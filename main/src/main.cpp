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

#include "generator/ProportionGenerator.hpp"
#include "particles/ParticleType.hpp"

int main(int argc, char** argv) {
    //object ownership setup
    //#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
     //   TDirectory::AddDirectory(kFALSE);
    //#endif
    //create root application
    //APP_TYPE app(APP_NAME, &argc, argv);

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

    using Pt = BASE_NS::ParticleType;
    using PtType = Pt::Type;

    proportionGenerator<PtType> gen{std::map<PtType,float>{
        {PtType::P_Pion,0.4},
        {PtType::N_Pion,0.4},
        {PtType::P_Kaon,0.05},
        {PtType::N_Kaon,0.05},
        {PtType::P_Prot,0.045},
        {PtType::N_Prot,0.045},
        {PtType::R_Kaon,0.01}

    }};
    //10^5 eventi
    for(int j = 0; j < 1e5; ++j){
        //genero le 100 particelle
        for(int i = 0; i < 1E2; ++i) {
            phi = gRandom->Uniform(0, 2 * TMath::Pi());
            AzimuthalAngles->Fill(phi);
            theta = gRandom->Uniform(0, TMath::Pi());
            PolarAngles->Fill(theta);
            P = gRandom->Exp(1);
            Impulse->Fill(P);
            //generate particle
            name=gen();
            ParticlesType->Fill(name);


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
                DecayProducts.push_back(p1);
                DecayProducts.push_back(p2);
            } else {
                BASE_NS::Particle p(name, P*TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));
                EventParticles.push_back(p);
                const double TransImp = std::sqrt(std::pow(p.GetPx(), 2) + std::pow(p.GetPy(), 2));
                TransverseImpulse->Fill(TransImp);
                Energies->Fill(p.GetEnergy());
            }
        }
        //EventParticles.insert(EventParticles.end(),
         //                     std::make_move_iterator(DecayProducts.begin()),
         //                     std::make_move_iterator(DecayProducts.end()));
        //loop scemo
        /*for(int i = 0; i < EventParticles.size(); ++i){
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
        }*/
    }
    auto *file = new TFile("Particle.root", "RECREATE");
    file->Write();
    //run application
    //app.Run();
    return 0;
}