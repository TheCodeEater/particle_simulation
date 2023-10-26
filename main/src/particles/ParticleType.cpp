//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/ParticleType.hpp"
#include <iostream>

namespace BASE_NS{

    ParticleType::ParticleType(const std::string &name, double mass, int charge):
        fName{name},
        fMass{mass},
        fCharge{charge}{}

    void ParticleType::Print() const {
        std::cout<<"Name: "<<fName<<'\n'
            <<"Mass: "<<fMass<<'\n'
            <<"Charge: "<<fCharge<<'\n';
    }

    const std::string &ParticleType::GetName() const {
        return fName;
    }

    double ParticleType::GetMass() const {
        return fMass;
    }

    int ParticleType::GetCharge() const {
        return fCharge;
    }

    double ParticleType::GetWidth() const {
        return 0;
    }
}