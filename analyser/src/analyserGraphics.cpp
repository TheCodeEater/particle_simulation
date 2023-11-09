//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>

namespace BASE_NS{
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser& analyser):
        fInputData{analyser.GetData()}, //get input data
        fSignalResult{analyser.GetDecaymentSignal()}, //run fit

        MassCanvas{new TCanvas("massCanvas","massCanvas",1200,800)},
        PartTypeCanvas{new TCanvas("PartTypeCanvas","PartTypeCanvas",1200,800)},
        DistributionsCanvas{new TCanvas("DistributionsCanvas","DistributionsCanvas",1200,800)},
        SumCanvas{new TCanvas("SumCanvas","SumCanvas",1200,800)},
        PulseCanvas{new TCanvas("PulseCanvas","PulseCanvas",1200,800)}{
                MassCanvas->Divide(3,2);
                        for(int i=0; i<fInputData->invMasses.size(); i++){
                        MassCanvas->cd(i);
                        fInputData->invMasses[i].Draw();
                         }
                PartTypeCanvas->cd(0);
                        fInputData->GeneratedTypes.Draw();
                DistributionsCanvas->Divide(2,1);
                        DistributionsCanvas->cd(0);
                            fInputData->PolarAngles.Draw();
                        DistributionsCanvas->cd(1);
                            fInputData->AzimuthAngles.Draw();
                SumCanvas->Divide(2,1);
                        SumCanvas->cd(0);
                                fSignalResult->signal1.Draw();
                        SumCanvas->cd(1);
                                fSignalResult->signal2.Draw();
                PulseCanvas->Divide(3,1);
                        PulseCanvas->cd(0);
                            fInputData->Pulse.Draw();
                        PulseCanvas->cd(1);
                            fInputData->TransPulse.Draw();
                        PulseCanvas->cd(2);
                             fInputData->Energy.Draw();



    
    }
}




