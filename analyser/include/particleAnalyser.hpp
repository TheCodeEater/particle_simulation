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

namespace BASE_NS{
    /**
     * This class encapsulates the data analysis for the K* decayment trace
     */
    class dataAnalyser{
        using histoContainer=std::unordered_map<std::string,TH1F>;
    public:
        /**
         * Construct the analyser class
         * @param path Path to the ROOT file holding the required objects
         */
        explicit dataAnalyser(std::string const& path);

        /**
         * Get a const reference to the underlying root TFile
         */
         [[nodiscard]] TFile const& GetFile() const;

    private:
        /**
         * A pointer to an instance of a root file
         */
        std::unique_ptr<TFile> fFile;
        /**
         * A pointer to the list of stored objects
         */
         histoContainer fList;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLEAANALYSER_HPP
