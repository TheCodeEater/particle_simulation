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
    public:
        /**
         * Construct the analyser class
         * @param path Path to the ROOT file holding the required objects
         */
        explicit dataAnalyser(std::string const& path);
        //Getters
        /**
         * Get a const reference to the underlying root TFile
         */
         [[nodiscard]] TFile const& GetFile() const;
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
          * @return True if consistent, false otherwise
          */
         [[maybe_unused]] bool CheckGeneration(double confidenceLevel);

    private:
        TFile fFile; ///Underlying root file
         dataContainerPtr fData; ///Underlying data container

         /**
          * Represent the result of distribution consistency check
          */
         class CheckResult{

         public:
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
             bool fSuccessful; /// wether the check was successful
             std::string fError; /// Arose errors
         };
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP
