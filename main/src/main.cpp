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

    BASE_NS::particleGenerator generator{};
    //run the simulation
    generator();
    auto *file = new TFile("Particle.root", "RECREATE");

    file->Close();
    //run application
    app.Run();
    return 0;
}