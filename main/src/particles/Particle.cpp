//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/Particle.hpp"

namespace BASE_NS{

    Particle::Particle(const std::string &name, double Px, double Py, double Pz):
        fParticleName{name},
        fPx{Px},
        fPy{Py},
        fPz{Pz}{

    }
}