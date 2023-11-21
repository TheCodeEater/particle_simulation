//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>
#include <iostream>

namespace BASE_NS {
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser &analyser) :
            fInputData{analyser.GetData()}, //get input data
            fSignalResult{analyser.GetDecaymentSignal()}, //run fit

            MassCanvas{new TCanvas("massCanvas", "Masse Invarianti", 1200, 800)},
            PartTypeCanvas{new TCanvas("PartTypeCanvas", "Tipi di particelle", 1200, 800)},
            DistributionsCanvas{new TCanvas("DistributionsCanvas", "Distribuzioni di generazione", 1200, 800)},
            SumCanvas{new TCanvas("SumCanvas", "Segnali estratti", 1200, 800)},
            PulseCanvas{new TCanvas("PulseCanvas", "Parametri meccanici", 1200, 800)} {
        const char *options{"HIST,SAME"};

        MassCanvas->Divide(3, 2);
        /*int i{};
        for(auto & node: fInputData->invMasses){
        MassCanvas->cd(i);
            //draw each histogram
            node.second.Draw();
            ++i; //increase pad counter
         }*/
        //MassCanvas->cd(0);
        //invariant masses
        MassCanvas->cd(1);
        fInputData->InvariantMassesDprod.Draw(options);

        //particle types
        PartTypeCanvas->Divide(1,0);
        PartTypeCanvas->cd(1);
        fInputData->ParticlesType.Draw(options);

        //generation distributions
        DistributionsCanvas->Divide(2, 1);
        DistributionsCanvas->cd(1);
        fInputData->PolarAngles.Draw(options);
        DistributionsCanvas->cd(2);
        fInputData->AzimuthalAngles.Draw(options);

        //signal canvas
        SumCanvas->Divide(2, 1);
        SumCanvas->cd(1);
        fSignalResult->signal1.Draw(options);
        SumCanvas->cd(2);
        fSignalResult->signal2.Draw(options);

        //mechanical canvas
        PulseCanvas->Divide(3, 1);
        PulseCanvas->cd(1);
        fInputData->Impulse.Draw(options);
        PulseCanvas->cd(2);
        fInputData->TransverseImpulse.Draw(options);
        PulseCanvas->cd(3);
        fInputData->Energies.Draw(options);

        MassCanvas->Modified();
        PartTypeCanvas->Modified();
        DistributionsCanvas->Modified();
        SumCanvas->Modified();
        PulseCanvas->Modified();

        MassCanvas->Update();
        PartTypeCanvas->Update();
        DistributionsCanvas->Update();
        SumCanvas->Update();
        PulseCanvas->Update();

        PartTypeCanvas->Print("particleTypes.gif");
        DistributionsCanvas->Print("generationDistributions.gif");
        SumCanvas->Print("sumCanvas.gif");
        PulseCanvas->Print("pulseCanvas.gif");


    }
}




