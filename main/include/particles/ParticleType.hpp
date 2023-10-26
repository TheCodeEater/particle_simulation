//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP

#include "Definitions.hpp"

#include <string>

namespace BASE_NS{
    class ParticleType{

    public:
        ParticleType(std::string const& name, double mass, int charge);
        void Print() const;

        [[nodiscard]] const std::string &GetName() const;

        [[nodiscard]] double GetMass() const;

        [[nodiscard]] int GetCharge() const;

    private:
        int fCharge;
        std::string fName;
        double fMass;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP
