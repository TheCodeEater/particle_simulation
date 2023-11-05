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
        using dataContainerPtr=std::unique_ptr<dataContainer>;
        using GenerationResult=std::unordered_map<std::string,TFitResultPtr>;
        /**
 * Represent the result of distribution consistency check
 */
        class CheckResult{

        public:
            CheckResult(bool success, std::string error);
            /**
             * Convert to bool
             * @return fSuccessful
             */
            explicit operator bool() const;

            /**
             * Get error string
             * @return error string
             */
            [[nodiscard]] std::string const& GetError() const;
        private:
            bool fSuccessful{}; /// wether the check was successful
            std::string fError{}; /// Arose errors
        };

        /**
         * Struct to hold the result of the required histogram difference
         */
        struct SignalResult{
            using HPtr=std::unique_ptr<TH1F>;
            using FitPtr=TFitResultPtr;

            HPtr signal1; /// Difference between the 2 kaon-pion histograms
            HPtr signal2; /// Difference between the concordant and discordant charge histogram
            FitPtr fitSignal1; /// Fit result ptr for signal 1
            FitPtr fitSignal2; /// Fit result ptr for signal 2
        };
        /**
         * Struct to hold the fit result for the generation data histograms
         */
        /*struct GenerationResult{
            using FitPtr=TFitResultPtr;

            FitPtr azimuth{}; /// Azimuth angle fit
            FitPtr polar{}; /// Polar angle fit
            FitPtr pulse{}; /// Pulse fit
        };*/

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
         [[nodiscard]] SignalResult GetDecaymentSignal() const;

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
