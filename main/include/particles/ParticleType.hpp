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
        virtual ~ParticleType()=default;

        virtual void Print() const;

        [[nodiscard]] const std::string &GetName() const;

        [[nodiscard]] double GetMass() const;

        [[nodiscard]] int GetCharge() const;

        [[nodiscard]] virtual double GetWidth() const;

    private:
        std::string fName;
        double fMass;
        int fCharge;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP
