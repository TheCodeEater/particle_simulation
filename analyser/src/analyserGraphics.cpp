//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>

namespace BASE_NS{
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser& analyser):
            fInputData{analyser.GetData()}, //get input data
            fSignalResult{analyser.GetDecaymentSignal()}, //run fit
            fCanvas{new TCanvas()},//create empty canvas
            fViews{}
    {
            fViews["generationHistograms"]=std::make_unique<TPad>(
                "genHist",
                "Histograms of generation distribution",
                1,1,0,0);
            fViews["kinematicHistograms"]=std::make_unique<TPad>(
                    "kineticHist",
                    "Histograms of particle kinetic data",
                    1,1,0,0
                    );
            fViews["invariantMassesHistograms"]=std::make_unique<TPad>(
                    "invMassHist",
                    "Histograms of invariant masses",
                    1,1,0,0
                    );
            fViews["signalHistograms"]=std::make_unique<TPad>(
                    "sigHist",
                    "Histograms of K* signals",
                    1,1,0,0
                    );
    }
}




