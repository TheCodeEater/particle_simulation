//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/ResonanceType.hpp"

#include <iostream>

namespace ResonanceSimulator {

    ResonanceType::ResonanceType(const int name, double mass, int charge, double width) :
            ParticleType{name, mass, charge},
            fWidth{width} {

    }

    double ResonanceType::GetWidth() const {
        return fWidth;
    }

    void ResonanceType::Print() const {
        ParticleType::Print();
        std::cout << "Resonance: " << fWidth << '\n';
    }
}