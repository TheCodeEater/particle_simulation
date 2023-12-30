//
// Created by Giacomo Errani on 10/10/23.
//
#include "Definitions.hpp"

#include "TApplication.h"
#include "TDirectory.h"
#include <TH1.h>
#include "TFile.h"

#include "generator/ParticleGenerator.hpp"
#include "particleStorage.hpp"
#include "particles/ParticleType.hpp"

int main(int argc, char **argv) {
    // object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
        TDirectory::AddDirectory(kFALSE);
        TH1::AddDirectory(kFALSE);
    #endif

    //allocate memory for particle data
    ResonanceSimulator::particleGenerator::loadParticles();

    //create generator object
    ResonanceSimulator::particleGenerator generator{};
    // run the simulation
    // save result in unique pointer
    std::unique_ptr<ResonanceSimulator::particleStorage> result{generator(1e5)};

    //write to file
    std::unique_ptr<TFile> output_file{new TFile("Particle.root", "RECREATE")};
    result->Write();
    output_file->Close();

    return 0;
}