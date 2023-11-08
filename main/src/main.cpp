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

int main(int argc, char** argv) {
    //object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
        TDirectory::AddDirectory(kFALSE);
    #endif
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    BASE_NS::Particle::AddParticleType(0, 0.13957, 1);
    BASE_NS::Particle::AddParticleType(1, 0.13957, -1);
    BASE_NS::Particle::AddParticleType(2, 0.49367, 1);
    BASE_NS::Particle::AddParticleType(3, 0.49367, -1);
    BASE_NS::Particle::AddParticleType(4, 0.93827, 1);
    BASE_NS::Particle::AddParticleType(5, 0.93827, -1);
    BASE_NS::Particle::AddParticleType(6, 0.89166, 0, 0.050);
    gRandom->SetSeed();

    std::vector<BASE_NS::Particle> EventParticles;
    std::vector<BASE_NS::Particle> DecayProducts;
    EventParticles.reserve(120);

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

    double theta{};
    double phi{};
    double P{};
    double x{};
    int name{};
    //10^5 eventi
    for(int j = 0; j < 20; ++j){
        //genero le 100 particelle
        for(int i = 0; i < 1E2; ++i){
            phi = gRandom->Uniform(0, 2 * TMath::Pi());
            AzimuthalAngles->Fill(phi);
            theta = gRandom->Uniform(0, TMath::Pi());
            PolarAngles->Fill(theta);
            P = gRandom->Exp(1);
            Impulse->Fill(P);
            //std::cout << "event: " << j << " particle: " << i << "\n";
            x=gRandom->Rndm();
            if (x < 0.4) {
                name = 0;
                ParticlesType->Fill(0);
            } else if (x < 0.8) {
                name = 1;
                ParticlesType->Fill(1);
            } else if (x < 0.85) {
                name = 2;
                ParticlesType->Fill(2);
            } else if (x < 0.9) {
                name = 3;
                ParticlesType->Fill(3);
            } else if (x < 0.945) {
                name = 4;
                ParticlesType->Fill(4);
            } else if (x < 0.99) {
                name = 5;
                ParticlesType->Fill(5);
            } else { name = 6;
                ParticlesType->Fill(6);}

            if(name == 6){
                double y = gRandom->Rndm();
                int name1{};
                int name2{};
                if(y < 0.5){
                    name1 = 0;
                    name2 = 3;
                } else {
                    name1 = 1;
                    name2 = 2;
                }
                BASE_NS::Particle p1(name1, 0, 0, 0);
                BASE_NS::Particle p2(name2, 0, 0, 0);
                BASE_NS::Particle pRes(6, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));

                if(pRes.Decay2body(p1, p2) != 0){
                    throw std::runtime_error("aaaaaaaaaaaaaaaah");
                }
                DecayProducts.emplace_back(p1);
                DecayProducts.emplace_back(p2);
            } else {
                BASE_NS::Particle p(name, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));
                EventParticles.emplace_back(p);
                const double TransImp = std::sqrt(std::pow(p.GetPx(), 2) + std::pow(p.GetPy(), 2));
                TransverseImpulse->Fill(TransImp);
                Energies->Fill(p.GetEnergy());
            }
        }

        EventParticles.insert(EventParticles.end(), DecayProducts.begin(), DecayProducts.end());
        //loop scemo
        for(int i = 0; i < EventParticles.size(); ++i){
            auto p = EventParticles[i];
            for( int j = i; j < EventParticles.size(); ++j){
                InvariantMasses->Fill(p.InvMass(EventParticles[j])); //MI tra tutti
                if(p.GetCharge() * EventParticles[j].GetCharge() == -1){
                    InvariantMassesAlld->Fill(p.InvMass(EventParticles[j]));
                }
                if(p.GetCharge() * EventParticles[j].GetCharge() == 1){
                    InvariantMassesAllc->Fill(p.InvMass(EventParticles[j]));
                }
                if(p.GetParticleName() == 0 && EventParticles[j].GetParticleName() == 3){
                    InvariantMassesPipKn->Fill(p.InvMass(EventParticles[j]));
                }
                if(p.GetParticleName() == 1 && EventParticles[j].GetParticleName() == 2){
                    InvariantMassesPinKp->Fill(p.InvMass(EventParticles[j]));
                }
                if(p.GetParticleName() == 0 && EventParticles[j].GetParticleName() == 2){
                    InvariantMassesPipKp->Fill(p.InvMass(EventParticles[j]));
                }
                if(p.GetParticleName() == 1 && EventParticles[j].GetParticleName() == 3){
                    InvariantMassesPinKn->Fill(p.InvMass(EventParticles[j]));
                }
            }
        }
        for(int i = 0; i < DecayProducts.size(); i+=2){
            auto p = DecayProducts[i];
            InvariantMassesDprod->Fill(p.InvMass(DecayProducts[i+1]));
        }
    }
    auto *file = new TFile("Particle.root", "RECREATE");
    file->Write();
    //run application
    //app.Run();
    return 0;
}