//
// Created by Giacomo Errani on 09/11/23.
//

#include "generator/ParticleGenerator.hpp"

#include "particles/Particle.hpp"
#include "particleStorage.hpp"

#include "TH1F.h"
#include "TMath.h"

namespace BASE_NS {
    void particleGenerator::loadParticles() {
        BASE_NS::Particle::AddParticleType(0, 0.13957, 1);
        BASE_NS::Particle::AddParticleType(1, 0.13957, -1);
        BASE_NS::Particle::AddParticleType(2, 0.49367, 1);
        BASE_NS::Particle::AddParticleType(3, 0.49367, -1);
        BASE_NS::Particle::AddParticleType(4, 0.93827, 1);
        BASE_NS::Particle::AddParticleType(5, 0.93827, -1);
        BASE_NS::Particle::AddParticleType(6, 0.89166, 0, 0.050);
    }

    particleGenerator::particleGenerator(unsigned int seed):
            fRandom{seed},
            fParticleGen{{
                {PTypeList::P_Pion,0.4},
                {PTypeList::N_Pion,0.4},
                {PTypeList::P_Kaon,0.05},
                {PTypeList::N_Kaon,0.05},
                {PTypeList::P_Prot,0.045},
                {PTypeList::N_Prot,0.045},
                {PTypeList::R_Kaon,0.01}}
            },
            fDecaymentGen{{
                {PTDecayList::P1,0.5},
                {PTDecayList::P2,0.5}
                    }
            }  {

    }

    void particleGenerator::operator()(unsigned int NEvents, unsigned int NParticlesPerEvent) {
        //save into particlestorage
        particleStorage ps{};
        //create default histograms
        particleStorage::makeDefaultHistograms(ps);
        //Particle type
        PStorage EventParticles{};
        PStorage DecayProducts{};
        //run simulation
        for(unsigned int j = 0; j < NEvents; ++j){
            //genero le 100 particelle
            for(unsigned int i = 0; i < NParticlesPerEvent; ++i) {
                //generate angles and pulse
                const double phi {gRandom->Uniform(0, 2 * TMath::Pi())};
                const double theta {gRandom->Uniform(0, TMath::Pi())};
                const double P {gRandom->Exp(1)};
                //add values to test histograms (must be done here)
                //because they are not tracked afterwards
                ps.AzimuthalAngles.Fill(phi);
                ps.PolarAngles.Fill(theta);
                ps.Impulse.Fill(P);

                //generate particle
                const PTypeList name{fParticleGen()};
                //add to histogram - try to move in another phase
                ps.ParticlesType.Fill(name);

                //if it is a resonance, make it decay
                if(name == PTypeList::R_Kaon){
                    //generate decayment pair
                    PTypeList name1{},name2{};

                    //generate decayment couple
                    if(fDecaymentGen()==PTDecayList::P1){
                        name1=PTypeList::P_Pion;
                        name2=PTypeList::N_Kaon;
                    }else{
                        name1=PTypeList::N_Pion;
                        name2=PTypeList::P_Kaon;
                    }

                    Particle p1(name1, 0, 0, 0);
                    Particle p2(name2, 0, 0, 0);
                    Particle pRes(PTypeList::R_Kaon, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));

                    if(pRes.Decay2body(p1, p2) != 0){
                        throw std::runtime_error("Decay2body failed!");
                    }
                    DecayProducts.push_back(p1);
                    DecayProducts.push_back(p2);
                    //add separately
                    EventParticles.push_back(p1);
                    EventParticles.push_back(p2);
                } else {
                    BASE_NS::Particle p(name, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));
                    EventParticles.push_back(p);
                    const double TransImp = std::sqrt(std::pow(p.GetPx(), 2) + std::pow(p.GetPy(), 2));
                    ps.TransverseImpulse.Fill(TransImp);
                    ps.Energies.Fill(p.GetEnergy());
                }
            }
            //loop scemo
            for(unsigned int i = 0; i < EventParticles.size(); ++i){
                auto const& p = EventParticles[i];
                for(unsigned int k = i; k < EventParticles.size(); ++k){
                    auto const& p2{EventParticles[k]};
                    auto invMass {p.InvMass(p2)};

                    ps.InvariantMasses.Fill(invMass); //MI tra tutti
                    if(p.GetCharge() * p2.GetCharge() == -1){
                        ps.InvariantMassesAlld.Fill(invMass);
                    }
                    if(p.GetCharge() * p2.GetCharge() == 1){
                        ps.InvariantMassesAllc.Fill(invMass);
                    }
                    if(p.GetParticleName() == 0 && p2.GetParticleName() == 3){
                        ps.InvariantMassesPipKn.Fill(invMass);
                    }
                    if(p.GetParticleName() == 1 && p2.GetParticleName() == 2){
                        ps.InvariantMassesPinKp.Fill(invMass);
                    }
                    if(p.GetParticleName() == 0 && p2.GetParticleName() == 2){
                        ps.InvariantMassesPipKp.Fill(invMass);
                    }
                    if(p.GetParticleName() == 1 && p2.GetParticleName() == 3){
                        ps.InvariantMassesPinKn.Fill(invMass);
                    }
                }
            }
            for(unsigned int i = 0; i < DecayProducts.size(); i+=2){
                auto& p = DecayProducts[i];
                ps.InvariantMassesDprod.Fill(p.InvMass(DecayProducts[i+1]));
            }
            EventParticles.clear();
        }
    }

} // BASE_NS