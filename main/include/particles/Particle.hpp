//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLE_HPP

#include "Definitions.hpp"
#include "particles/ParticleType.hpp"
#include "particles/ResonanceType.hpp"

#include <map>
#include <string>

namespace BASE_NS{
    class Particle{
        using pTypeStorage=std::map<std::string, std::unique_ptr<ParticleType>>;
    public:
        explicit Particle(std::string const& name,double Px=0, double Py=0, double Pz=0);

        [[nodiscard]] const std::string &GetParticleName() const;

        static void AddParticleType(std::string const& name, double mass, int charge, double width=0);
        static void PrintParticleList();

        void SetParticleType(std::string const& name);
        void PrintData() const;

        void SetP(double px, double py, double pz);
        [[nodiscard]] double GetPx() const;
        [[nodiscard]] double GetPy() const;
        [[nodiscard]] double GetPz() const;

        [[nodiscard]] double GetMass() const;
        double GetEnergy() const;
        [[nodiscard]] double InvMass(Particle const& p) const;

    private:
        static pTypeStorage fParticleType;
        static constexpr int fMaxNumParticleType{10};

        std::string fParticleName;
        double fPx;
        double fPy;
        double fPz;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLE_HPP
