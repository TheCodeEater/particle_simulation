//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/ParticleType.hpp"
#include "particles/ResonanceType.hpp"
#include "Definitions.hpp"

using namespace ResonanceSimulator;

int main() {
    ParticleType part{"part1", 1, 16};
    ResonanceType pawrt{"pawrt1", 2, 32, 8.};

    part.Print();
    pawrt.Print();
}