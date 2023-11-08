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
            fViews{}
    {
            fViews["generationHistograms"]=std::make_unique<TPad>(
                "genHist",
                "Histograms of generation distribution",
                0,0,1,1);
            fViews["kinematicHistograms"]=std::make_unique<TPad>(
                    "kineticHist",
                    "Histograms of particle kinetic data",
                    0,0,1,1
                    );
            fViews["invariantMassesHistograms"]=std::make_unique<TPad>(
                    "invMassHist",
                    "Histograms of invariant masses",
                    0,0,1,1
                    );
            fViews["signalHistograms"]=std::make_unique<TPad>(
                    "sigHist",
                    "Histograms of K* signals",
                    0,0,1,1
                    );
    }
}




