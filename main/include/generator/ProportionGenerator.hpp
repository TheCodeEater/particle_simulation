//
// Created by Giacomo Errani on 08/11/23.
//

#ifndef PROPORTIONGENERATOR_HPP
#define PROPORTIONGENERATOR_HPP

#include "particles/ParticleType.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <numeric>

#include "TRandom.h"

namespace ResonanceSimulator {

/**
 * This class generates, based on definite proportions, the elements it is instructed to
 * @tparam GEN The type of the object to be generated
 *
 * NOTE: probability is given in percentile in integer values (to avoid FP problems)
 */
    template<typename GEN>
    class ProportionGenerator {
        /**
         * Struct representing a node of generation, holding values with cumulative weight
         */
        struct Node {
            GEN fValue{}; /// Value
            float fCumulativeProbability{}; /// Relevant cumulative probability
        };
        /**
         * Construct the generator
         * @param sourceData Map associating values to be generated to relevant probability values
         */
    public:
        using probType = float;/// type to represent probability

        explicit ProportionGenerator(std::map<GEN, probType> sourceData) :
                fNodes{} {
            //check probability
            auto totalProb = std::accumulate(sourceData.begin(),
                                             sourceData.end(),
                                             0, [](auto const &acc, auto const &node) {
                        return acc + node.second; //sum probabilities
                    });

            if (std::abs(totalProb - 100) < 0.01) { //FP epsilon
                throw std::runtime_error{"Sum of probability is not 100!"};
            }

            //allocate space for the nodes
            fNodes.reserve(sourceData.size());
            //fill f nodes
            probType accumulator{0}; //hold accumulate probability
            for (auto const &node: sourceData) {
                accumulator += node.second; //accumulate probabilities
                fNodes.push_back({node.first, accumulator});
            }
        }

        /**
         * Generate function
         * @return A randomly generated value, based on the input data
         */
        GEN operator()() {
            //genrate value, cast to int
            probType y{static_cast<probType>(gRandom->Rndm())};

            for (auto const &node: fNodes) {
                //if the value generated is less than, i am generated
                if (y < node.fCumulativeProbability) {
                    return node.fValue; //end cycle
                }
            }
            throw std::runtime_error{"Cannot generate!"};
        }

    private:
        std::vector<Node> fNodes;


    };

}


#endif
