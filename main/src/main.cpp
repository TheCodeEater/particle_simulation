//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "TDirectory.h"

#include "Definitions.hpp"

#include "particles/Particle.hpp"

int main(int argc, char** argv) {
    //object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
        TDirectory::AddDirectory(kFALSE);
    #endif
        BASE_NS::Particle::AddParticleType("PI+",0.13957, +1);
        BASE_NS::Particle::AddParticleType("PI-",0.13957, -1);
        BASE_NS::Particle::AddParticleType("K+",0.49367, +1);
        BASE_NS::Particle::AddParticleType("K-",0.49367, -1);
        BASE_NS::Particle::AddParticleType("P+",0.93827, +1);
        BASE_NS::Particle::AddParticleType("P-",0.93827, -1);
        BASE_NS::Particle::AddParticleType("K*",0.89166, 0,0.050); //resonance width only in unstable partivcle


    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects

    //do stuff

    //run application
    app.Run();
    return 0;
}