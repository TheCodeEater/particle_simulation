//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/Particle.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

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

    void Particle::PrintData() const {
        std::cout<<"Name:"<<fParticleName<<'\n'
            <<"PX"<<fPx<<'\n'
            <<"PY"<<fPy<<'\n'
            <<"PZ"<<fPz<<'\n';
    }

    void Particle::SetP(double px, double py, double pz) {
        fPx=px;
        fPy=py;
        fPz=pz;
    }

    double Particle::GetPx() const {
        return fPx;
    }

    double Particle::GetPy() const {
        return fPy;
    }

    double Particle::GetPz() const {
        return fPz;
    }

    double Particle::InvMass(const Particle &p) const {
        return std::sqrt(
                std::pow(GetEnergy()+p.GetEnergy(),2)
                - (std::pow(fPx+p.GetPx(),2)
                    +std::pow(fPy+p.GetPy(),2)
                    +std::pow(fPz+p.GetPz(),2))
                );
    }

    [[nodiscard]] double Particle::GetMass() const {
        return fParticleType.at(fParticleName)->GetMass();
    }

    double Particle::GetEnergy() const {
        return std::sqrt(std::pow(GetMass(),2)+
            std::pow(fPx,2)+
            std::pow(fPy,2)+
            std::pow(fPz,2));
    }
}