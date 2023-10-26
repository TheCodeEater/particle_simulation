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
        //check that the requested particle name exist
        if(fParticleType.find(name)==fParticleType.end()){
            throw std::out_of_range{"Non c'e', perche' non c'e'?"};
        }
    }
}