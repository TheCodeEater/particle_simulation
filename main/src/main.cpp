//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "TDirectory.h"
#include "TRandom.h"

#include "TRandom.h"
#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include <iostream>
#include "../include/particles/Particle.hpp"
#include "Definitions.hpp"

#include "generator/ParticleGenerator.hpp"

#include "generator/ProportionGenerator.hpp"
#include "particles/ParticleType.hpp"

#include "particleStorage.hpp"

#include <deque>

int main(int argc, char** argv) {
    //object ownership setup
    //#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
     //   TDirectory::AddDirectory(kFALSE);
    //#endif
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //load particles
    BASE_NS::particleGenerator::loadParticles();

    std::deque<BASE_NS::Particle> EventParticles{};
    //track decay products both in all events and separately
    std::deque<BASE_NS::Particle> DecayProducts{};

    TH1F *ParticlesType = new TH1F("ParticlesType", "Particles Type", 7, 0, 7);
    TH1F *AzimuthalAngles = new TH1F("AzimuthalAngles", "Azimuthal Angles", 100, 0, 2*TMath::Pi());
    TH1F *PolarAngles = new TH1F("PolarAngles", "Polar Angles", 100, 0, TMath::Pi());
    TH1F *Impulse = new TH1F("Impulse", "Impulse", 100, 0, 5);
    TH1F *TransverseImpulse = new TH1F("TransverseImpulse", "Transverse Impulse", 100, 0, 5);
    TH1F *Energies = new TH1F("Energies", "Energies", 100, 0, 10);
    TH1F *InvariantMasses = new TH1F("InvariantMasses", "Invariant Masses", 100, 0, 10);
    InvariantMasses->Sumw2();
    TH1F *InvariantMassesAlld = new TH1F("InvariantMassesAlld", "Invariant Masses Alld", 100, 0, 10);
    TH1F *InvariantMassesAllc = new TH1F("InvariantMassesAllc", "Invariant Masses Allc", 100, 0, 10);
    TH1F *InvariantMassesPipKn = new TH1F("InvariantMassesPipKn", "Invariant Masses PipKn", 100, 0, 10);
    TH1F *InvariantMassesPinKp = new TH1F("InvariantMassesPinKp", "Invariant Masses PinKp", 100, 0, 10);
    TH1F *InvariantMassesPipKp = new TH1F("InvariantMassesPipKp", "Invariant Masses PipKp", 100, 0, 10);
    TH1F *InvariantMassesPinKn = new TH1F("InvariantMassesPinKn", "Invariant Masses PinKn", 100, 0, 10);
    TH1F *InvariantMassesDprod = new TH1F("InvariantMassesDprod", "Invariant Masses Dprod", 100, 0, 10);

    double x{};

    using Pt = BASE_NS::ParticleType;
    using PtType = Pt::Type;

    BASE_NS::proportionGenerator<PtType> pGen{std::map<PtType,float>{
        {PtType::P_Pion,0.4},
        {PtType::N_Pion,0.4},
        {PtType::P_Kaon,0.05},
        {PtType::N_Kaon,0.05},
        {PtType::P_Prot,0.045},
        {PtType::N_Prot,0.045},
        {PtType::R_Kaon,0.01}

    }};

    BASE_NS::proportionGenerator<Pt::DecaymentType> decGen{{
        {Pt::DecaymentType::P1,0.5},
        {Pt::DecaymentType::P2,0.5}
    }
    };
    //10^5 eventi
    for(int j = 0; j < 1e5; ++j){
        //genero le 100 particelle
        for(int i = 0; i < 1E2; ++i) {
            //generate angles and pulse
            const double phi {gRandom->Uniform(0, 2 * TMath::Pi())};
            const double theta {gRandom->Uniform(0, TMath::Pi())};
            const double P {gRandom->Exp(1)};
            //add values to test histograms (must be done here)
            //because they are not tracked afterwards
            AzimuthalAngles->Fill(phi);
            PolarAngles->Fill(theta);
            Impulse->Fill(P);

            //generate particle
            const PtType name{pGen()};
            //add to histogram - try to move in another phase
            ParticlesType->Fill(name);

            //if it is a resonance, make it decay
            if(name == PtType::R_Kaon){
                //generate decayment pair
                PtType name1{},name2{};

                //generate decayment couple
                if(decGen()==Pt::DecaymentType::P1){
                    name1=PtType::P_Pion;
                    name2=PtType::N_Kaon;
                }else{
                    name1=PtType::N_Pion;
                    name2=PtType::P_Kaon;
                }

                BASE_NS::Particle p1(name1, 0, 0, 0);
                BASE_NS::Particle p2(name2, 0, 0, 0);
                BASE_NS::Particle pRes(PtType::R_Kaon, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));

                if(pRes.Decay2body(p1, p2) != 0){
                    throw std::runtime_error("aaaaaaaaaaaaaaaah");
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
                TransverseImpulse->Fill(TransImp);
                Energies->Fill(p.GetEnergy());
            }
        }
        //loop scemo
        for(int i = 0; i < EventParticles.size(); ++i){
            auto const& p = EventParticles[i];
            for( int k = i; k < EventParticles.size(); ++k){
                auto const& p2{EventParticles[k]};
                auto invMass {p.InvMass(p2)};

                InvariantMasses->Fill(invMass); //MI tra tutti
                if(p.GetCharge() * p2.GetCharge() == -1){
                    InvariantMassesAlld->Fill(invMass);
                }
                if(p.GetCharge() * p2.GetCharge() == 1){
                    InvariantMassesAllc->Fill(invMass);
                }
                if(p.GetParticleName() == 0 && p2.GetParticleName() == 3){
                    InvariantMassesPipKn->Fill(invMass);
                }
                if(p.GetParticleName() == 1 && p2.GetParticleName() == 2){
                    InvariantMassesPinKp->Fill(invMass);
                }
                if(p.GetParticleName() == 0 && p2.GetParticleName() == 2){
                    InvariantMassesPipKp->Fill(invMass);
                }
                if(p.GetParticleName() == 1 && p2.GetParticleName() == 3){
                    InvariantMassesPinKn->Fill(invMass);
                }
            }
        }
        for(int i = 0; i < DecayProducts.size(); i+=2){
            auto p = DecayProducts[i];
            InvariantMassesDprod->Fill(p.InvMass(DecayProducts[i+1]));
        }
        EventParticles.clear();
    }
    auto *file = new TFile("Particle.root", "RECREATE");

    file->Close();
    //run application
    app.Run();
    return 0;
}