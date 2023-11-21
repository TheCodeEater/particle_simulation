//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLE_HPP

#include "Definitions.hpp"
#include "particles/ParticleType.hpp"
#include "particles/ResonanceType.hpp"

#include <memory>
#include <vector>
#include <string>
#include <memory>


namespace ResonanceSimulator {
    class Particle {
        using pTypeStorage = std::vector<std::unique_ptr<ParticleType>>;
    public:
        explicit Particle(int name, double Px = 0, double Py = 0, double Pz = 0);

        [[nodiscard]] int GetParticleName() const;

        static void AddParticleType(int name, double mass, int charge, double width = 0);

        static void PrintParticleList();

        void SetParticleType(int name);

        void PrintData() const;

        void SetP(double px, double py, double pz);

        [[nodiscard]] double GetPx() const;

        [[nodiscard]] double GetPy() const;

        [[nodiscard]] double GetPz() const;

        [[nodiscard]] int GetCharge() const;

        [[nodiscard]] double GetMass() const;

        [[nodiscard]] double GetEnergy() const;

        [[nodiscard]] double InvMass(Particle const &p) const;

        int Decay2body(Particle &dau1, Particle &dau2) const;

    private:
        void Boost(double bx, double by, double bz);

        static pTypeStorage fParticleType;
        static constexpr int fMaxNumParticleType{10};

        int fParticleName;
        double fPx;
        double fPy;
        double fPz;

        //ClassDef(Particle, 1);
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLE_HPP
