//
// Created by Giacomo Errani on 26/10/23.
//
#include "particles/Particle.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdlib>

#include "TMath.h"

namespace BASE_NS{

    Particle::Particle(const int name, double Px, double Py, double Pz):
        fParticleName{name},
        fPx{Px},
        fPy{Py},
        fPz{Pz}{
        //check that the requested particle name exist
        fParticleType.at(name);
    }

    int Particle::GetParticleName() const {
        return fParticleName;
    }

    void Particle::AddParticleType(int name, double mass, int charge, double width) {
        if(fParticleType.size()==fMaxNumParticleType){
            throw std::runtime_error{"Maximum particle number reached!"};
        }
        //fParticleType.at(name); //se non c'è, inserisci
            if(width==0){ //may cause troubles with FP numbers
                fParticleType[name]=std::make_unique<ParticleType>(name,mass,charge);
            }else{
                fParticleType[name]=std::make_unique<ResonanceType>(name,mass,charge,width);
            }
    }

    void Particle::SetParticleType(int name) {
        fParticleType.at(name);
        fParticleName=name;
    }

    void Particle::PrintParticleList() {
        std::for_each(fParticleType.cbegin(),fParticleType.cend(),[](auto const& node){
            node->Print();
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

    //initialise map
    Particle::pTypeStorage Particle::fParticleType(120);

    int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
        if(GetMass() == 0.0){
            std::cout << "there is no decay if mass is zero";
            return 1;
        }

        double massMot = GetMass();
        double massDau1 = dau1.GetMass();
        double massDau2 = dau2.GetMass();

        double x1, x2, w, y1;

        double invnum = 1./RAND_MAX;
        do {
            x1 = 2.0 * rand()*invnum - 1.0;
            x2 = 2.0 * rand()*invnum - 1.0;
            w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 );

        w = sqrt( (-2.0 * log( w ) ) / w );
        y1 = x1 * w;

        massMot += fParticleType[fParticleName]->GetWidth() * y1;

        if(massMot < massDau1 + massDau2){
            std::cout <<"Decayment cannot be preformed because mass is too low in this channel\n";
            return 2;
        }

        double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

        double norm = 2*M_PI/RAND_MAX;

        double phi = rand()*norm;
        double theta = rand()*norm*0.5 - M_PI/2.;
        dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
        dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

        double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

        double bx = fPx/energy;
        double by = fPy/energy;
        double bz = fPz/energy;

        dau1.Boost(bx,by,bz);
        dau2.Boost(bx,by,bz);

        return 0;
    }

    void Particle::Boost(double bx, double by, double bz) {
        double energy = GetEnergy();

        //Boost this Lorentz vector
        double b2 = bx*bx + by*by + bz*bz;
        double gamma = 1.0 / sqrt(1.0 - b2);
        double bp = bx*fPx + by*fPy + bz*fPz;
        double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

        fPx += gamma2*bp*bx + gamma*bx*energy;
        fPy += gamma2*bp*by + gamma*by*energy;
        fPz += gamma2*bp*bz + gamma*bz*energy;
    }

    int Particle::GetCharge() const {
        return fParticleType[fParticleName]->GetCharge();
    }

    //ClassImp(Particle);
}