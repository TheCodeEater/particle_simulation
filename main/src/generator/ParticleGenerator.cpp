//
// Created by Giacomo Errani on 09/11/23.
//

#include "generator/ParticleGenerator.hpp"

#include "particles/Particle.hpp"

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

    }

} // BASE_NS