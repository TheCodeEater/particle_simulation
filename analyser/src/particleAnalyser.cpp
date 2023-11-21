//
// Created by Giacomo Errani on 02/11/23.
//
#include "particleAnalyser.hpp"

#include "particleStorage.hpp"
#include "dataStructures/signalFitResult.hpp"
#include "dataStructures/genCheckResult.hpp"

#include "TFitResult.h"
#include "TFitResultPtr.h"

#include <sstream>

namespace ResonanceSimulator {

    dataAnalyser::dataAnalyser(const std::string &path) :
    //create empty TList
            fData{} {
        //open the file in read only mode
        TFile data_source{path.c_str(), "READ"};

        //check that the file was opened correctly
        if (!data_source.IsOpen()) {
            throw std::runtime_error{"Cannot open root file. Path: " + path};
        }

        //load data
        fData = dataContainerPtr{
                dynamic_cast<dataContainer *>(data_source.Get("ResonanceSimulator::particleStorage"))
        };
        //particles_decay_data
    }

    dataAnalyser::dataContainerPtr dataAnalyser::GetData() {
        return fData;
    }

    dataAnalyser::dataContainerConstPtr dataAnalyser::GetData() const {
        return fData;
    }

    [[maybe_unused]] CheckResult dataAnalyser::CheckGeneration(double confidenceLevel) {
        //check type proportion generation
        //result variable data
        bool success{};
        std::stringstream errors{};
        //check histograms generated according to PDF
        {
            //Get angular data
            auto &azimuthal{fData->AzimuthalAngles};
            auto &polar{fData->PolarAngles};
            auto &pulse{fData->Impulse};

            //fit data storage
            std::unordered_map<const char *, TFitResultPtr> fits;

            //run the fit, saving results in tfit ptr
            fits.insert({"Azimuth", azimuthal.Fit("pol0", "S")});
            fits.insert({"Polar", polar.Fit("pol0", "S")});
            fits.insert({"Pulse", pulse.Fit("expo", "S")});

            //check fit
            for (auto const &node: fits) {
                auto &fitPtr{node.second};

                if (fitPtr->Prob() <= confidenceLevel) {
                    success = false;
                    errors << node.first << " fit failed. Observed probability: " << fitPtr->Prob() << "\n";
                }
            }
        }
        //check particle types histogram
        {
            auto &genHist{fData->ParticlesType};
            //for each bin
            for (int i{}; i < genHist.GetNbinsX(); ++i) {
                //compare with required generation
            }
        }
        //create data structure and return
        return CheckResult{success, errors.str()};
    }

    std::shared_ptr<SignalResult> dataAnalyser::GetDecaymentSignal() const {
        auto signal1 = TH1F{
                fData->InvariantMassesDecayD - fData->InvariantMassesDecayC
                //fData->invMasses["DiscordantPK"]-fData->invMasses["ConcordantPK"]
        };

        auto signal2 = TH1F{
                fData->InvariantMassesAllc - fData->InvariantMassesAlld};

        //run fit
        auto fit1 = signal1.Fit("gaus", "S");
        auto fit2 = signal2.Fit("gaus", "S");
        //return the 2 signals
        return std::make_shared<SignalResult>(signal1, signal2, fit1, fit2);
    }

    dataAnalyser::GenerationResult dataAnalyser::GetGenerationFits() const {
        //Get angular data
        auto &azimuthal{fData->AzimuthalAngles};
        auto &polar{fData->PolarAngles};
        auto &pulse{fData->Impulse};

        //fit data storage
        std::unordered_map<std::string, TFitResultPtr> fits;

        //run the fit, saving results in tfit ptr
        fits.insert({"Azimuth", azimuthal.Fit("pol0", "S")});
        fits.insert({"Polar", polar.Fit("pol0", "S")});
        fits.insert({"Pulse", pulse.Fit("expo", "S")});

        return fits;
    }

}