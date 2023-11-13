//
// Created by Giacomo Errani on 09/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP

#include "Definitions.hpp"
#include "TRandom3.h"
#include "generator/ProportionGenerator.hpp"
#include "particles/Particle.hpp"

#include "particleStorage.hpp"

#include <deque>

namespace BASE_NS {

    /**
     * This class encapsulates particle generation, decayment processing, invariant masses distributions
     */
    class particleGenerator {
        using randGen=TRandom3; /// type to be used as random generator
        using PTypeList = ParticleType::Type; /// alias to list of possible particle types
        using PTDecayList= ParticleType::DecaymentType; ///alias to list of possible decayments
        using PStorage=std::deque<Particle>;

        public:
            explicit particleGenerator(unsigned seed=0);
            /**
             * Register particle list into particle container
             * Data is hard-coded
             */
            static void loadParticles();

            /**
             * Run the simulation
             * @param NEvents Number of dacyment events to be processed
             * @param NParticlesPerEvent Number of paarticles to be generated per event
             */
            particleStorage* operator()(unsigned NEvents=1e5, unsigned NParticlesPerEvent=1e2);

    private:
        //helper functions
        void calculateInvariantMass(PStorage const& EventParticles,
                                    PStorage const& DecayProducts,
                                    particleStorage& dataStorage) const;

        randGen fRandom; /// Random generator
        proportionGenerator<PTypeList> fParticleGen;
        proportionGenerator<PTDecayList> fDecaymentGen;
    };

} // BASE_NS

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP
