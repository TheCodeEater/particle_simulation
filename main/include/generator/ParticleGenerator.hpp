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

namespace ResonanceSimulator {

    /**
     * This class encapsulates particle generation, decayment processing, invariant masses distributions
     */
    class particleGenerator {
        using randGen = TRandom3; /// type to be used as random generator
        using PTypeList = ParticleType::Type; /// alias to list of possible particle types
        using PTDecayList = ParticleType::DecaymentType; ///alias to list of possible decayments
        using PStorage = std::deque<Particle>;

    public:
        explicit particleGenerator(unsigned seed = 0);

        /**
         * Register particle list into particle container
         * Data is hard-coded
         */
        static void loadParticles();

        /**
         * Run the simulation
         * @param NEvents Number of dacyment events to be processed
         * @param NParticlesPerEvent Number of paarticles to be generated per event
         * @return A pointer to a data structure holding the result of the generation
         *
         * Note: the returned pointer's structure is dynamically allocated and you are responsible
         * for its lifetime management. Consider storing it in a smart pointer.
         */
        particleStorage *operator()(unsigned NEvents = 1e5, unsigned NParticlesPerEvent = 1e2);

    private:
        //helper functions
        /**
         * Helper function used to better ecapsulate the particle generation
         * @param EventParticles Reference to the container of generated particles
         * @param DecayProducts Reference to the container of the decay products
         * @param dataStorage Struct holding histograms
         */
        static void calculateInvariantMass(PStorage const &EventParticles,
                                    PStorage const &DecayProducts,
                                    particleStorage &dataStorage) ;

        randGen fRandom; /// Random generator
        proportionGenerator<PTypeList> fParticleGen;
        proportionGenerator<PTDecayList> fDecaymentGen;

        static bool isSameCharge(const Particle &p, const Particle &p2);

        static bool checkConcordantDecayCouples(const PTypeList &p1_name, const PTypeList &p2_name);

        static bool checkDiscordantDecayCouples(const PTypeList &p1_name, const PTypeList &p2_name);
    };

} // ResonanceSimulator

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP
