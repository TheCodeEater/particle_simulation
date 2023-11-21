//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_RESONANCETYPE_HPP
#define ROOT_TEMPLATE_PROJECT_RESONANCETYPE_HPP

#include "Definitions.hpp"
#include "particles/ParticleType.hpp"

namespace BASE_NS {
    class ResonanceType : public ParticleType {

    public:
        ResonanceType(int const name, double mass, int charge, double width);

        [[nodiscard]] double GetWidth() const override;

        void Print() const override;

    private:
        double fWidth;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_RESONANCETYPE_HPP
