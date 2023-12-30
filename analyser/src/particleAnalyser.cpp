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
        //normalize generation distirbutions
        //for bin width, i chose bin 1 but all bins have the same width
        fData->PolarAngles.Scale(1./(fData->PolarAngles.GetEntries()*fData->PolarAngles.GetBinWidth(1)));
        fData->AzimuthalAngles.Scale(1./(fData->AzimuthalAngles.GetEntries()*fData->AzimuthalAngles.GetBinWidth(1)));
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
        auto signal1 = new TH1F{
                fData->InvariantMassesDecayD
                //fData->invMasses["DiscordantPK"]-fData->invMasses["ConcordantPK"]
        };

        signal1->Add(&fData->InvariantMassesDecayC,-1);

        signal1->SetName("DecaySignal1");
        signal1->SetTitle("K* signal from decay products");

        auto signal2 = new TH1F{
                fData->InvariantMassesAlld};
        signal2->Add(&fData->InvariantMassesAllc,-1);

        signal2->SetName("DecaySignal2");
        signal2->SetTitle("K* signal from all particles");

        //run fit
        TF1 fit1{"FIT_SIGNAL_1","gaus",0,10};
        signal1->Fit(&fit1);

        TF1 fit2{"FIT_SIGNAL_2","gaus",0,10};
        signal2->Fit(&fit2);

        TF1 fit3{"FIT_SIGNAL_RAW","gaus",0,10};
        fData->InvariantMassesDprod.Fit(&fit3);
        //return the 2 signals
        return std::make_shared<SignalResult>(signal1, signal2, fit1, fit2, fit3);
    }

    dataAnalyser::GenerationResult dataAnalyser::GetGenerationFits() const {
        //Get angular data
        auto &azimuthal{fData->AzimuthalAngles};
        auto &polar{fData->PolarAngles};
        auto &pulse{fData->Impulse};

        //fit data storage
        GenerationResult fits;

        //run the fit, saving results in tfit ptr
        fits.insert({"Azimuth", TF1{"FIT_AZIMUTH","pol0",0,10}});
        fits.insert({"Polar", TF1{"FIT_POLAR","pol0",0,10}});
        fits.insert({"Pulse", TF1{"FIT_PULSE","expo",0,10}});

        azimuthal.Fit(&fits["Azimuth"]);
        polar.Fit(&fits["Polar"]);
        pulse.Fit(&fits["Pulse"]);

        return fits;
    }

}