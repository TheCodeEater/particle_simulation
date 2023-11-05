//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>

BASE_NS::AnalyzerGraphics::AnalyzerGraphics(dataAnalyser& analyser):
    //fDataAnalyser{std::move(analyser)}, //shared pointer already copied. Just move
    //fSignalResult{fDataAnalyser->GetDecaymentSignal()}, //run fit
    fActiveScreen{Menu::mainMenu}, //set main menu
    fCanvas{new TCanvas()}//create empty canvas
        {
            //Get input data
            auto inputData=analyser.GetData();
            //populate menu lists
            //populate geneated data menu
            {
                auto genList=std::make_unique<TList>();
                genList->Add(& inputData->GeneratedTypes);
                genList->Add(& inputData->PolarAngles);
                genList->Add(& inputData->AzimuthAngles);

                fGraphicData[Menu::generationHistograms]=std::move(genList);
            }
            //populate kinematic histograms
            {
                auto kinList=std::make_unique<TList>();
                kinList->Add(&inputData->Pulse);
                kinList->Add(&inputData->Energy);
                kinList->Add(&inputData->TransPulse);

                fGraphicData[Menu::kinematicHistograms]=std::move(kinList);
            }
            //populate invMass histograms
            {
                auto invList=std::make_unique<TList>();

                //for each histogram about invariant mass
                for(auto& node: inputData->invMasses){
                    invList->Add(std::addressof(node.second)); //get ptr to underlying data
                }

                fGraphicData[Menu::invMassHistograms]=std::move(invList);
            }
            //populate signal histograms
            {

            }

        }

void BASE_NS::AnalyzerGraphics::ShowScreen(BASE_NS::Menu screen) {
    fActiveScreen=screen; //set the currenlty active screen
}

