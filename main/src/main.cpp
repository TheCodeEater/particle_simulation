//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "TDirectory.h"
#include "TRandom.h"

#include "Definitions.hpp"
#include "particles/Particle.hpp"

#include <algorithm>

int main(int argc, char** argv) {
    //object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
        TDirectory::AddDirectory(kFALSE);
    #endif
        BASE_NS::Particle::AddParticleType("PI+",0.13957, +1);
        BASE_NS::Particle::AddParticleType("PI-",0.13957, -1);
        BASE_NS::Particle::AddParticleType("K+",0.49367, +1);
        BASE_NS::Particle::AddParticleType("K-",0.49367, -1);
        BASE_NS::Particle::AddParticleType("P+",0.93827, +1);
        BASE_NS::Particle::AddParticleType("P-",0.93827, -1);
        BASE_NS::Particle::AddParticleType("K*",0.89166, 0,0.050); //resonance width only in unstable partivcle

        //event generation
        std::vector<BASE_NS::Particle> particles{};
        particles.reserve(120);
        std::generate_n(std::back_inserter(particles),100,[](){
            //generate particle motion params
            const double phi{gRandom->Uniform(0,2*M_PI)};
            const double theta{gRandom->Uniform(0,M_PI)};
            const double P{gRandom->Exp(1)};

            //pick particle type
            std::string particle_name{};
            const double type{gRandom->Rndm()};

            if(type>=0 && type<=0.4){
                particle_name="PI+";
            }else if(type<0.8){
                particle_name="PI-";
            }else if(type<0.85){
                particle_name="K+";
            }else if(type<0.9){
                particle_name="K-";
            }else if(type<0.945){
                particle_name="P+";
            }else if(type<0.99){
                particle_name="P-";
            }else{
                particle_name="K*";
            }

            //convert to cartesian
            const double px{};
            const double py{};
            const double pz{};

            return BASE_NS::Particle{particle_name,px,py,pz};
        });

    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects

    //do stuff

    //run application
    app.Run();
    return 0;
}