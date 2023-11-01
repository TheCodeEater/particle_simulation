//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "TDirectory.h"
#include "TRandom.h"
#include "TMath.h"

#include "../include/particles/Particle.hpp"
#include "Definitions.hpp"

int main(int argc, char** argv) {
    //object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
        TDirectory::AddDirectory(kFALSE);
    #endif
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    BASE_NS::Particle::AddParticleType("Pi+", 0.13957, 1);
    BASE_NS::Particle::AddParticleType("P-+", 0.13957, -1);
    BASE_NS::Particle::AddParticleType("K+", 0.49367, 1);
    BASE_NS::Particle::AddParticleType("K-", 0.49367, -1);
    BASE_NS::Particle::AddParticleType("P+", 0.93827, 1);
    BASE_NS::Particle::AddParticleType("P-", 0.93827, -1);
    BASE_NS::Particle::AddParticleType("K*", 0.89166, 0, 0.050);
    gRandom->SetSeed();

    std::vector<BASE_NS::Particle> EventParticles;
    EventParticles.reserve(120);

    double theta{};
    double phi{};
    double P{};
    double x{};
    std::string name{};
    //10^5 eventi
    for(int j = 0; j < 1E5; ++j){
        //genero le 100 particelle
        for(int i = 0; i < 1E2; ++i){
            phi = gRandom->Uniform(0, 2 * TMath::Pi());
            theta = gRandom->Uniform(0, TMath::Pi());
            P = gRandom->Exp(1);

            x=gRandom->Rndm();
            if (x < 0.4) {
                name = "Pi+";
            } else if (x < 0.8) {
                name = "Pi-";
            } else if (x < 0.85) {
                name = "K+";
            } else if (x < 0.9) {
                name = "K-";
            } else if (x < 0.945) {
                name = "P+";
            } else if (x < 0.99) {
                name = "P-";
            } else { name = "K*"; }

            EventParticles.emplace_back(name, P * TMath::Sin(theta)*TMath::Cos(phi), P*TMath::Sin(theta)*TMath::Sin(phi), P*TMath::Cos(theta));
        }
    }
    //run application
    app.Run();
    return 0;
}