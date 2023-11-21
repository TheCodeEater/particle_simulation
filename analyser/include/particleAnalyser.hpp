//
// Created by Giacomo Errani on 02/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP

#include "Definitions.hpp"
#include "TFile.h"
#include "TH1.h"
#include <string>
#include <unordered_map>

#include "particleStorage.hpp"
#include "dataStructures/genCheckResult.hpp"
#include "dataStructures/signalFitResult.hpp"

namespace BASE_NS {
    /**
     * This class encapsulates the data analysis for the K* decayment trace.
     * The class acts as a mere analysis running tool: results are NOT stored internally. The user is required
     * to handle their storage
     *
     * The class provides shared ownership about source data, to allow further
     * manipulation before running the true analysis
     */
    class dataAnalyser {
        using dataContainer = particleStorage;
        using dataContainerPtr = std::shared_ptr<dataContainer>;
        using dataContainerConstPtr = std::shared_ptr<const dataContainer>;
        using GenerationResult = std::unordered_map<std::string, TFitResultPtr>;

    public:
        /**
         * Construct the analyser class
         * @param path Path to the ROOT file holding the required objects
         */
        explicit dataAnalyser(std::string const &path);

        /**
         * Get a const reference to underlying dataContainer structure
         */
        [[nodiscard]] dataContainerPtr GetData();

        /**
        * Get a const pointer to underlying dataContainer structure
        */
        [[nodiscard]] dataContainerConstPtr GetData() const;

        //analysers
        /**
         * Check wether the generated particles are consistent with the generation parameters
         *
         * Particle type generation is said to be consistent if the required value is compatible
         * with the observed one (i.e. falls into the uncertainty interval)
         *
         * Angular and pulse distribution are compatible depeding on the Chi square.
         * The test uses a defualt confidence level given
         *
         * Due to root internal fitting this function cannot be const
         *
         * @param The confidence level
         * @return A structure holding the result, both generally and specific error codes
         */
        // MOVE TO TESTS
        [[maybe_unused]] CheckResult CheckGeneration(double confidenceLevel);

        /**
         * Run the decayment signal analysis
         * @return A shared pointer to SignalResult structure holding K* decayment signal distribution along
         * with gaussian fit results
         *
         * Note: the returned structure is generated ex-novo at each invocation. Nothing is stored internally
         * about this analysis result
         */
        [[nodiscard]] std::shared_ptr<SignalResult> GetDecaymentSignal() const;

        /**
         * Fit the histograms of the data used to generate decayment events and particles
         * @return Struct holding fit result data
         */
        [[nodiscard]] GenerationResult GetGenerationFits() const;

    private:
        dataContainerPtr fData; ///Underlying data container
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP
