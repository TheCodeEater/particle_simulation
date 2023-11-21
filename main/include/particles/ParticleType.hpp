//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP

#include "Definitions.hpp"

#include <string>

namespace BASE_NS {


    class ParticleType {

    public:
        enum Type {
            P_Pion, N_Pion, P_Kaon, N_Kaon, P_Prot, N_Prot, R_Kaon
        };
        enum DecaymentType {
            P1,//P+ K-
            P2
        };//P- K+

        ParticleType(int name, double mass, int charge);

        virtual ~ParticleType() = default;

        virtual void Print() const;

        [[nodiscard]] int GetName() const;

        [[nodiscard]] double GetMass() const;

        [[nodiscard]] int GetCharge() const;

        [[nodiscard]] virtual double GetWidth() const;

    private:
        Type fName;
        double fMass;
        int fCharge;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLETYPE_HPP
