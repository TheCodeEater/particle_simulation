//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "particles/ParticleType.hpp"

namespace ResonanceSimulator {
    class ResonanceType : public ParticleType {

    public:
        ResonanceType(int name, double mass, int charge, double width);

        [[nodiscard]] double GetWidth() const override;

        void Print() const override;

    private:
        double fWidth;
    };
}

#endif
