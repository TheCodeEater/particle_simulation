//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

BASE_NS::AnalyzerGraphics::AnalyzerGraphics():
    fActiveScreen{Menu::mainMenu},
    fCanvas{new TCanvas()} {

}

void BASE_NS::AnalyzerGraphics::ShowScreen(BASE_NS::Menu screen) {
    fActiveScreen=screen; //set the currenlty active screen
}

