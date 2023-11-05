//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

BASE_NS::AnalyzerGraphics::AnalyzerGraphics(std::shared_ptr<dataAnalyser> analyser):
    fDataAnalyser{std::move(analyser)}, //shared pointer already copied. Just move
    fSignalResult{fDataAnalyser->GetDecaymentSignal()}, //run fit
    fActiveScreen{Menu::mainMenu}, //set main menu
    fCanvas{new TCanvas()}//create empty canvas
        {
            //populate menus
            //get input data
            auto rawData{fDataAnalyser->GetData()};



        }

void BASE_NS::AnalyzerGraphics::ShowScreen(BASE_NS::Menu screen) {
    fActiveScreen=screen; //set the currenlty active screen
}

