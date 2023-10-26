//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/Particle.hpp"

#include <algorithm>

namespace BASE_NS{

    Particle::Particle(const std::string &name, double Px, double Py, double Pz):
        fParticleName{name},
        fPx{Px},
        fPy{Py},
        fPz{Pz}{
        //check that the requested particle name exist
        if(fParticleType.find(name)==fParticleType.end()){
            throw std::out_of_range{"Non c'e', perche' non c'e'?"};
        }
    }

    const std::string &Particle::GetParticleName() const {
        return fParticleName;
    }

    void Particle::AddParticleType(const std::string &name, double mass, int charge, double width) {
        if(fParticleType.size()==fMaxNumParticleType){
            throw std::runtime_error{"Maximum particle number reached!"};
        }
        if(fParticleType.find(name)==fParticleType.end()){ //se non c'è, inserisci
            if(width==0){ //may cause troubles with FP numbers
                fParticleType[name]=std::make_unique<ParticleType>(name,mass,charge);
            }else{
                fParticleType[name]=std::make_unique<ResonanceType>(name,mass,charge,width);
            }
        }else{
            throw std::runtime_error{"A particle with the same name already exists!"};
        }
    }

    void Particle::SetParticleType(const std::string &name) {
        if(fParticleType.find(name)==fParticleType.end()){
            throw std::out_of_range{"Non c'e', perche' non c'e'?"};
        }
        fParticleName=name;
    }

    void Particle::PrintParticleList() {
        std::for_each(fParticleType.cbegin(),fParticleType.cend(),[](auto const& node){
            node.second->Print();
        });
    }
}