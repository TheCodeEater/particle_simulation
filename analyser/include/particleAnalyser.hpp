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

namespace BASE_NS{
    /**
     * This class encapsulates the data analysis for the K* decayment trace
     */
    class dataAnalyser{
        using dataContainer=particleStorage;
        using dataContainerPtr=std::shared_ptr<dataContainer>;
        using GenerationResult=std::unordered_map<std::string,TFitResultPtr>;

    public:
        /**
         * Construct the analyser class
         * @param path Path to the ROOT file holding the required objects
         */
        explicit dataAnalyser(std::string const& path);
         /**
          * Get a const reference to underlying dataContainer structure
          */
          [[nodiscard]] dataContainer& GetData();
        /**
        * Get a const reference to underlying dataContainer structure
        */
        [[nodiscard]] dataContainer const& GetData() const;

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
          * @return A SignalResult structure holding K* decayment signal distribution along
          * with gaussian fit results
          */
         [[nodiscard]] std::shared_ptr<SignalResult> GetDecaymentSignal() const;

         /**
          * Fit the histograms of the data used to generate decayment events and particles
          * @return Struct holding fit result data
          */
         [[nodiscard]] GenerationResult GetGenerationFits() const;

    private:
         dataContainerPtr fData; ///Underlying data container
         std::shared_ptr<SignalResult> fSignal; /// Signal analysis result
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP
