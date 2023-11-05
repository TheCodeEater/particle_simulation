//
// Created by Giacomo Errani on 02/11/23.
//
#include "particleAnalyser.hpp"

#include <utility>
#include "Definitions.hpp"

#include "particleStorage.hpp"

#include "TFitResult.h"
#include "TFitResultPtr.h"

#include <sstream>

namespace BASE_NS{

    dataAnalyser::dataAnalyser(const std::string &path):
        //open the root file in read only mode
        fFile{path.c_str(),"READ"},
        //create empty TList
        fData{}{

        //check that the file was opened correctly
        if(fFile.IsOpen()){
            throw std::runtime_error{"Cannot open root file. Path: "+path};
        }

        //load data
        fData=std::unique_ptr<dataContainer> (
                dynamic_cast<dataContainer*>(fFile.Get("particles_decay_data"))
                );
    }

    TFile const &dataAnalyser::GetFile() const {
        return fFile;
    }

    dataAnalyser::dataContainer &dataAnalyser::GetData() {
        return *fData;
    }

    const dataAnalyser::dataContainer &dataAnalyser::GetData() const {
        return *fData;
    }

    [[maybe_unused]] dataAnalyser::CheckResult dataAnalyser::CheckGeneration(double confidenceLevel) {
        //check type proportion generation
        //result variable data
        bool success{};
        std::stringstream errors{};
        //check histograms generated according to PDF
        {
            //Get angular data
            auto & azimuthal{fData->AzimuthAngles};
            auto & polar{fData->PolarAngles};
            auto & pulse{fData->Pulse};

            //fit data storage
            std::unordered_map<const char*,TFitResultPtr> fits;

            //run the fit, saving results in tfit ptr
            fits.insert({"Azimuth",azimuthal.Fit("pol0","S")});
            fits.insert({"Polar",polar.Fit("pol0","S")});
            fits.insert({"Pulse",pulse.Fit("expo","S")});

            //check fit
            for(auto const& node : fits){
                auto& fitPtr{node.second};

                if(fitPtr->Prob()<=confidenceLevel){
                    success=false;
                    errors<<node.first<<" fit failed. Observed probability: "<<fitPtr->Prob()<<"\n";
                }
            }
        }
        //check particle types histogram
        {
            auto& genHist{fData->GeneratedTypes};
            //for each bin
            for(int i{};i<genHist.GetNbinsX();++i){
                //compare with required generation
            }
        }
        //create data structure and return
        return CheckResult{success,errors.str()};
    }

    dataAnalyser::Result dataAnalyser::GetDecaymentSignal() const {
        auto signal1=std::make_unique<TH1F>(
                fData->invMasses["DiscordantPK"]-fData->invMasses["ConcordantPK"]);

        auto signal2=std::make_unique<TH1F>(
                fData->invMasses["AllDiscordant"]-fData->invMasses["AllConcordant"]);

        //run fit
        auto fit1=signal1->Fit("gaus","S");
        auto fit2=signal2->Fit("gaus","S");
        //return the 2 signals
        return {std::move(signal1),std::move(signal2),fit1,fit2};
    }

    dataAnalyser::CheckResult::operator bool() const {
        return fSuccessful;
    }

    std::string const &dataAnalyser::CheckResult::GetError() const {
        return fError;
    }

    dataAnalyser::CheckResult::CheckResult(bool success, std::string error):
        fSuccessful{success},
        fError{std::move(error)}{

    }
}