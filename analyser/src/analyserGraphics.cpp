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
            fCanvasContainer{} {
        //create canvases
        {
        CanvasPtr MassCanvas{new TCanvas("massCanvas", "Masse Invarianti", 1200, 800)};
        CanvasPtr PartTypeCanvas{new TCanvas("ParticleTypeCanvas", "Tipi di particelle", 1200, 800)};
        CanvasPtr DistributionsCanvas{new TCanvas("DistributionsCanvas", "Distribuzioni di generazione", 1200, 800)};
        CanvasPtr SumCanvas{new TCanvas("SignalCanvas", "Segnali estratti", 1200, 800)};
        CanvasPtr PulseCanvas{new TCanvas("PulseCanvas", "Parametri meccanici", 1200, 800)};

        //register canvases
        fCanvasContainer[MassCanvas->GetName()] = std::move(MassCanvas);
        fCanvasContainer[PartTypeCanvas->GetName()] = std::move(PartTypeCanvas);
        fCanvasContainer[DistributionsCanvas->GetName()] = std::move(DistributionsCanvas);
        fCanvasContainer[SumCanvas->GetName()] = std::move(SumCanvas);
        fCanvasContainer[PulseCanvas->GetName()] = std::move(PulseCanvas);
    }

        //draw all canvases
        drawCanvases();

        //notify that canvas have been drawn
        graphicSetup();

        //write histograms to file
        writeHistograms();


    }

    void AnalyzerGraphics::writeHistograms() const {
        for(auto& canvas: fCanvasContainer){
            canvas.second->Print((
                    std::string{canvas.second->GetName()}+".pdf"
                    ).c_str());
        }

    }

    void AnalyzerGraphics::drawCanvases() {
        const char *options{"HIST,SAME"};

        //bind references to ptr for simplicit
        CanvasPtr& MassCanvas{fCanvasContainer["massCanvas"]};
        CanvasPtr& PartTypeCanvas{fCanvasContainer["ParticleTypeCanvas"]};
        CanvasPtr& DistributionsCanvas{fCanvasContainer["DistributionsCanvas"]};
        CanvasPtr& SumCanvas{fCanvasContainer["SignalCanvas"]};
        CanvasPtr& PulseCanvas{fCanvasContainer["PulseCanvas"]};

        //invariant masses
        MassCanvas->Divide(3, 2);

        MassCanvas->cd(1);
        fInputData->InvariantMassesDprod.Draw(options);

        //particle types
        PartTypeCanvas->Divide(1, 0);
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
    }

    void AnalyzerGraphics::graphicSetup() {
        for(auto& canvas: fCanvasContainer){
            canvas.second->Modified();
            canvas.second->Update();
        }
    }
}




