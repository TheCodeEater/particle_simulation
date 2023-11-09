//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>

namespace BASE_NS{
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser& analyser):
            fInputData{analyser.GetData()}, //get input data
            fSignalResult{analyser.GetDecaymentSignal()}, //run fit
            fCanvas{new TCanvas("mainCanvas","K* signal analyser",1200,800)},//create empty canvas
    {
            
    }
}




