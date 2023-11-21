//
// Created by Giacomo Errani on 10/10/23.
//
#include <deque>
#include <iostream>

#include "../include/particles/Particle.hpp"
#include "Definitions.hpp"
#include "TApplication.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRint.h"
#include "generator/ParticleGenerator.hpp"
#include "generator/ProportionGenerator.hpp"
#include "particleStorage.hpp"
#include "particles/ParticleType.hpp"

int main(int argc, char **argv) {
    // object ownership setup
    // #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
    //    TDirectory::AddDirectory(kFALSE);
    // #endif
    // create root application
    // APP_TYPE app(APP_NAME, &argc, argv);

    ResonanceSimulator::particleGenerator::loadParticles();

    ResonanceSimulator::particleGenerator generator{};
    // run the simulation
    // save result in unique pointer
    std::unique_ptr<ResonanceSimulator::particleStorage> result{generator(1e5)};
    auto *file = new TFile("Particle.root", "RECREATE");
    result->Write();
    file->Close();
    // run application
    // app.Run();
    return 0;
}