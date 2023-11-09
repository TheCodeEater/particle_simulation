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
            fRandom{seed}{

    }
} // BASE_NS