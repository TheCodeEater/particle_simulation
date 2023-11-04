//
// Created by Giacomo Errani on 02/11/23.
//
#include "particleAnalyser.hpp"
#include "Definitions.hpp"

#include "particleStorage.hpp"

#include "TFitResult.h"
#include "TFitResultPtr.h"

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

        //populate the list from tfile
        //get the TList
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

    [[maybe_unused]] bool dataAnalyser::CheckGeneration() {
        //check type proportion generation

        //check angular proportions
        {
            //Get angular data
            auto & azimuthal{fData->AzimuthAngles};
            auto & polar{fData->PolarAngles};

            //run the fit
            auto azFit=azimuthal.Fit("pol0","S");
            auto polFit=polar.Fit("pol0","S");

            azFit->Prob();
        }
    }
}