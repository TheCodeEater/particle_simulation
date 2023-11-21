//
// Created by Giacomo Errani on 09/11/23.
//

#include "generator/ParticleGenerator.hpp"

#include "particles/Particle.hpp"
#include "particleStorage.hpp"

#include "TH1F.h"
#include "TMath.h"

#include "TFile.h"

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

    particleGenerator::particleGenerator(unsigned int seed) :
            fRandom{seed},
            fParticleGen{{
                                 {PTypeList::P_Pion, 0.4},
                                 {PTypeList::N_Pion, 0.4},
                                 {PTypeList::P_Kaon, 0.05},
                                 {PTypeList::N_Kaon, 0.05},
                                 {PTypeList::P_Prot, 0.045},
                                 {PTypeList::N_Prot, 0.045},
                                 {PTypeList::R_Kaon, 0.01}}
            },
            fDecaymentGen{{
                                  {PTDecayList::P1, 0.5},
                                  {PTDecayList::P2, 0.5}
                          }
            } {

    }

    particleStorage *particleGenerator::operator()(unsigned int NEvents, unsigned int NParticlesPerEvent) {
        //save into particlestorage
        std::unique_ptr<particleStorage> dataStorage{new particleStorage{}};
        //create default histograms
        particleStorage::makeDefaultHistograms(*dataStorage);
        //Particle type
        PStorage EventParticles{};
        PStorage DecayProducts{};
        //run simulation
        for (unsigned int j = 0; j < NEvents; ++j) {
            //genero le 100 particelle
            for (unsigned int i = 0; i < NParticlesPerEvent; ++i) {
                //generate angles and pulse
                const double phi{gRandom->Uniform(0, 2 * TMath::Pi())};
                const double theta{gRandom->Uniform(0, TMath::Pi())};
                const double P{gRandom->Exp(1)};
                //add values to test histograms (must be done here)
                //because they are not tracked afterwards
                dataStorage->AzimuthalAngles.Fill(phi);
                dataStorage->PolarAngles.Fill(theta);
                dataStorage->Impulse.Fill(P);

                //generate particle
                const PTypeList name{fParticleGen()};
                //add to histogram - try to move in another phase
                dataStorage->ParticlesType.Fill(name);

                //if it is a resonance, make it decay
                if (name == PTypeList::R_Kaon) {
                    //generate decayment pair
                    PTypeList name1{}, name2{};

                    //generate decayment couple
                    if (fDecaymentGen() == PTDecayList::P1) {
                        name1 = PTypeList::P_Pion;
                        name2 = PTypeList::N_Kaon;
                    } else {
                        name1 = PTypeList::N_Pion;
                        name2 = PTypeList::P_Kaon;
                    }

                    Particle p1(name1, 0, 0, 0);
                    Particle p2(name2, 0, 0, 0);
                    Particle pRes(PTypeList::R_Kaon, P * TMath::Sin(theta) * TMath::Cos(phi),
                                  P * TMath::Sin(theta) * TMath::Sin(phi), P * TMath::Cos(theta));

                    if (pRes.Decay2body(p1, p2) != 0) {
                        throw std::runtime_error("Decay2body failed!");
                    }
                    DecayProducts.push_back(p1);
                    DecayProducts.push_back(p2);
                    //add separately
                    EventParticles.push_back(p1);
                    EventParticles.push_back(p2);
                } else {
                    BASE_NS::Particle p(name, P * TMath::Sin(theta) * TMath::Cos(phi),
                                        P * TMath::Sin(theta) * TMath::Sin(phi), P * TMath::Cos(theta));
                    EventParticles.push_back(p);
                    const double TransImp = std::sqrt(std::pow(p.GetPx(), 2) + std::pow(p.GetPy(), 2));
                    dataStorage->TransverseImpulse.Fill(TransImp);
                    dataStorage->Energies.Fill(p.GetEnergy());
                }
            }
            calculateInvariantMass(EventParticles, DecayProducts, *dataStorage);

            EventParticles.clear();
            DecayProducts.clear();
        }

        //release ownership on object and return raw pointer
        return dataStorage.release();

        //auto *file = new TFile("Particle.root", "RECREATE");
        //dataStorage.Write();
        //write single histograms for debugging purposes
        /*dataStorage.InvariantMasses.Write();
        dataStorage.InvariantMassesAlld.Write();
        dataStorage.InvariantMassesAllc.Write();
        dataStorage.InvariantMassesPipKn.Write();
        dataStorage.InvariantMassesPinKp.Write();
        dataStorage.InvariantMassesPipKp.Write();
        dataStorage.InvariantMassesPinKn.Write();
        dataStorage.InvariantMassesDprod.Write();*/
        //file->Close();
    }

    void particleGenerator::calculateInvariantMass(const particleGenerator::PStorage &EventParticles,
                                                   const particleGenerator::PStorage &DecayProducts,
                                                   particleStorage &dataStorage) const {

        //loop throught the dataset, comparing each particle with the others
        for (unsigned int i = 0; i < EventParticles.size(); ++i) {
            auto const &p = EventParticles[i];
            for (unsigned int k = i; k < EventParticles.size(); ++k) {
                auto const &p2{EventParticles[k]};
                auto invMass{p.InvMass(p2)};

                PTypeList p1_name{static_cast<PTypeList>(p.GetParticleName())};
                PTypeList p2_name{static_cast<PTypeList>(p2.GetParticleName())};

                //invariant mass between all particles
                dataStorage.InvariantMasses.Fill(invMass);

                //invariant mass depending on charge

                //concordant charge
                if (isSameCharge(p, p2)) {
                    dataStorage.InvariantMassesAllc.Fill(invMass);

                    //check that the particle couple is of the decay product type
                    if (checkConcordantDecayCouples(p1_name, p2_name)) {
                        dataStorage.InvariantMassesDecayC.Fill(invMass);
                    }
                }
                    //discordant charge
                else /*if(!isSameCharge(p, p2))*/{
                    dataStorage.InvariantMassesAlld.Fill(invMass);

                    if (checkDiscordantDecayCouples(p1_name, p2_name)) {
                        dataStorage.InvariantMassesDecayD.Fill(invMass);
                    }
                }

                //invariant mass between particles that can either be or not be result
                //of the decay
                /*if(p.GetParticleName() == PTypeList::P_Pion && p2.GetParticleName() == PTypeList::N_Kaon){
                    dataStorage.InvariantMassesPipKn.Fill(invMass);
                }
                if(p.GetParticleName() == PTypeList::N_Pion && p2.GetParticleName() == PTypeList::P_Kaon){
                    dataStorage.InvariantMassesPinKp.Fill(invMass);
                }
                if(p.GetParticleName() == PTypeList::P_Pion && p2.GetParticleName() == PTypeList::P_Kaon){
                    dataStorage.InvariantMassesPipKp.Fill(invMass);
                }
                if(p.GetParticleName() == PTypeList::N_Pion && p2.GetParticleName() == PTypeList::N_Kaon){
                    dataStorage.InvariantMassesPinKn.Fill(invMass);
                }*/
            }
        }
        //generate invariant mass for decay products
        //since they are inserted in pair after each decay
        //taking 2 each time ensures invariant mass is computed only for children
        //of the same unstable particle
        for (unsigned int i = 0; i < DecayProducts.size(); i += 2) {
            auto &p = DecayProducts[i];
            dataStorage.InvariantMassesDprod.Fill(p.InvMass(DecayProducts[i + 1]));
        }
    }

    bool particleGenerator::checkDiscordantDecayCouples(const particleGenerator::PTypeList &p1_name,
                                                        const particleGenerator::PTypeList &p2_name) {
        if (p1_name == PTypeList::P_Pion) {
            if (p2_name == PTypeList::N_Kaon) {
                return true;
            }
        } else if (p1_name == PTypeList::P_Kaon) {//symmetric: Kaon+/Pion+
            if (p2_name == PTypeList::N_Pion) {
                return true;
            }
        }
        //same with negative
        if (p1_name == PTypeList::N_Pion) {
            if (p2_name == PTypeList::P_Kaon) {
                return true;
            }
        } else if (p1_name == PTypeList::N_Kaon) {//symmetric: Kaon+/Pion+
            if (p2_name == PTypeList::P_Pion) {
                return true;
            }
        }
        return false;
    }

    bool particleGenerator::checkConcordantDecayCouples(const particleGenerator::PTypeList &p1_name,
                                                        const particleGenerator::PTypeList &p2_name) {//decay product check
//Pion+ / Kaon +
        if (p1_name == PTypeList::P_Pion) {
            if (p2_name == PTypeList::P_Kaon) {
                return true;
            }
        } else if (p1_name == PTypeList::P_Kaon) {//symmetric: Kaon+/Pion+
            if (p2_name == PTypeList::P_Pion) {
                return true;
            }
        }
        //same with negative
        if (p1_name == PTypeList::N_Pion) {
            if (p2_name == PTypeList::N_Kaon) {
                return true;
            }
        } else if (p1_name == PTypeList::N_Kaon) {//symmetric: Kaon+/Pion+
            if (p2_name == PTypeList::N_Pion) {
                return true;
            }
        }
        return false;
    }

    bool particleGenerator::isSameCharge(const Particle &p, const Particle &p2) {
        return p.GetCharge() * p2.GetCharge() > 0;
    }


} // BASE_NS