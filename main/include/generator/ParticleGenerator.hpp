//
// Created by Giacomo Errani on 09/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP

#include "Definitions.hpp"
#include "TRandom3.h"

namespace BASE_NS {

    /**
     * This class encapsulates particle generation, decayment processing, invariant masses distributions
     */
    class particleGenerator {
        using randGen=TRandom3; /// type to be used as random generator
        public:
            explicit particleGenerator(unsigned seed=0);
            /**
             * Register particle list into particle container
             * Data is hard-coded
             */
            static void loadParticles();

    private:
        randGen fRandom; /// Random generator
    };

} // BASE_NS

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEGENERATOR_HPP
