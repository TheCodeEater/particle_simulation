//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>

namespace BASE_NS{
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser& analyser):
        fInputData{analyser.GetData()}, //get input data
        fSignalResult{analyser.GetDecaymentSignal()}, //run fit

        MassCanvas{new TCanvas("massCanvas",1200,800)},
        PartTypeCanvas{new TCanvas("PartTypeCanvas",1200,800)},
        DistributionsCanvas{new TCanvas("DistributionsCanvas",1200,800)},
        SumCanvas{new TCanvas("SumCanvas",1200,800)}{
                MassCanvas->Divide(3,2);
                        for(int i=0; i<fInputData->invMassess.size(); i++){
                        MassCanvas->cd(i);
                        fInputData->invMasses[i].Draw();
                         }
                PartTypeCanvas->cd(0);
                        GeneratedTypes->Draw();
                DistributionsCanvas->Divide(2,1);
                        DistributionsCanvas->cd(0);
                                PolarAngles->Draw();
                        DistributionsCanvas->cd(1);
                                AzimuthAngles->cd();
                SumCanvas->Divide(2,1);
                        SumCanvas->cd(0);
                                
                        SumCanvas->cd(1);


    
    }
}




