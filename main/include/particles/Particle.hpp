//
// Created by Giacomo Errani on 25/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLE_HPP

#include "Definitions.hpp"
#include "particles/ParticleType.hpp"

#include <map>
#include <string>

namespace BASE_NS{
    class Particle{
    public:
        explicit Particle(std::string const& name,double Px=0, double Py=0, double Pz=0);
    private:
        static std::map<std::string, std::unique_ptr<ParticleType>> fParticleType;
        static constexpr int fMaxNumParticleType{10};

        std::string fParticleName;
        double fPx;
        double fPy;
        double fPz;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLE_HPP