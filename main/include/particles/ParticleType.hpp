//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <string>

namespace ResonanceSimulator {

    class ParticleType {

    public:
        enum Type { /// particle type enum
            P_Pion, N_Pion, P_Kaon, N_Kaon, P_Prot, N_Prot, R_Kaon
        };
        enum DecaymentType { /// decay result type enum
            P1,//P+ K-
            P2 //P- K+
        };

        ParticleType(int name, double mass, int charge);

        virtual ~ParticleType() = default;

        virtual void Print() const;

        [[nodiscard]] int GetName() const;

        [[nodiscard]] double GetMass() const;

        [[nodiscard]] int GetCharge() const;

        [[nodiscard]] virtual double GetWidth() const;

    private:
        Type fName; ///name of the particle, expressed as an enum constant
        double fMass;
        int fCharge;
    };
}

#endif
