//
// Created by Giacomo Errani on 05/11/23.
//
#include "analyserGraphics.hpp"

#include <algorithm>
#include <iostream>

namespace ResonanceSimulator {
    AnalyzerGraphics::AnalyzerGraphics(dataAnalyser &analyser) :
            fInputData{analyser.GetData()}, //get input data
            fSignalResult{analyser.GetDecaymentSignal()}, //run fit
            fGenerationDistributionFit{analyser.GetGenerationFits()},
            fCanvasContainer{},
            fLegendContainer{}{
        //create canvases
        {
        CanvasPtr MassCanvas{new TCanvas("massCanvas", "Masse Invarianti", 1200, 800)};
        CanvasPtr PartTypeCanvas{new TCanvas("ParticleTypeCanvas", "Tipi di particelle", 1200, 800)};
        CanvasPtr DistributionsCanvas{new TCanvas("DistributionsCanvas", "Distribuzioni di generazione", 1200, 800)};
        CanvasPtr SumCanvas{new TCanvas("SignalCanvas", "Segnali estratti", 1200, 800)};
        CanvasPtr DynamicsCanvas{new TCanvas("DynamicsCanvas", "Parametri meccanici", 1200, 800)};

        //register canvases
        fCanvasContainer[MassCanvas->GetName()] = std::move(MassCanvas);
        fCanvasContainer[PartTypeCanvas->GetName()] = std::move(PartTypeCanvas);
        fCanvasContainer[DistributionsCanvas->GetName()] = std::move(DistributionsCanvas);
        fCanvasContainer[SumCanvas->GetName()] = std::move(SumCanvas);
        fCanvasContainer[DynamicsCanvas->GetName()] = std::move(DynamicsCanvas);
    }
        //create legends
        //allocate memory
        fLegendContainer.reserve(11);

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
        //CanvasPtr& PartTypeCanvas{fCanvasContainer["ParticleTypeCanvas"]};
        CanvasPtr& DistributionsCanvas{fCanvasContainer["DistributionsCanvas"]};
        CanvasPtr& SignalCanvas{fCanvasContainer["SignalCanvas"]};
        CanvasPtr& DynamicsCanvas{fCanvasContainer["DynamicsCanvas"]};

        //invariant masses
        MassCanvas->Divide(3, 2);

        MassCanvas->cd(1);
        fInputData->InvariantMasses.Draw(options);
        MassCanvas->cd(2);
        fInputData->InvariantMassesAllc.Draw(options);
        MassCanvas->cd(3);
        fInputData->InvariantMassesAlld.Draw(options);
        MassCanvas->cd(4);
        fInputData->InvariantMassesDecayC.Draw(options);
        MassCanvas->cd(5);
        fInputData->InvariantMassesDecayD.Draw(options);
        MassCanvas->cd(6);
        fInputData->InvariantMassesDprod.Draw(options);

        //particle types
        /*PartTypeCanvas->Divide(1, 0);
        PartTypeCanvas->cd(1);
        fInputData->ParticlesType.Draw(options);*/

        //generation distributions
        DistributionsCanvas->Divide(2, 2);
        DistributionsCanvas->cd(1);
        fInputData->PolarAngles.Draw(options);
        fGenerationDistributionFit["Polar"].Draw("SAME");

        DistributionsCanvas->cd(2);
        fInputData->AzimuthalAngles.Draw(options);
        fGenerationDistributionFit["Azimuth"].Draw("SAME");

        DistributionsCanvas->cd(3);
        fInputData->Impulse.Draw(options);
        fGenerationDistributionFit["Pulse"].Draw("SAME");

        DistributionsCanvas->cd(4);
        fInputData->ParticlesType.Draw(options);

        //signal canvas
        SignalCanvas->Divide(3, 1);
        SignalCanvas->cd(1);
        fSignalResult->signal1.Draw(options);
        fSignalResult->fitSignal1.Draw("SAME");
        SignalCanvas->cd(2);
        fSignalResult->signal2.Draw(options);
        fSignalResult->fitSignal2.Draw("SAME");
        SignalCanvas->cd(3);
        fInputData->InvariantMassesDprod.Draw(options);
        fSignalResult->fitSignal3.Draw("SAME");

        //mechanical canvas
        DynamicsCanvas->Divide(2, 1);
        //DynamicsCanvas->cd(1);
        //fInputData->Impulse.Draw(options);
        DynamicsCanvas->cd(1);
        fInputData->TransverseImpulse.Draw(options);
        DynamicsCanvas->cd(2);
        fInputData->Energies.Draw(options);
    }

    void AnalyzerGraphics::graphicSetup() {
        for(auto& canvas: fCanvasContainer){
            canvas.second->Modified();
            canvas.second->Update();
        }
    }

    void AnalyzerGraphics::PrintFitResult() const {
        auto const& genFit{fGenerationDistributionFit};

        auto const& polar{genFit.at("Polar")};
        auto const& azimuth{genFit.at("Azimuth")};
        auto const& impulse{genFit.at("Pulse")};
        //Print distribution fit
        std::cout<<"=========== DISTRIBUTION FIT RESULT ===============\n";

        std::cout<<"Impulse: \n"<<"Constant: "<<impulse.GetParameter(0)<<"\n"
            <<"Slope: "<<impulse.GetParameter(1)<<"\n"
            <<"Chi/Dof: "<<impulse.GetChisquare()/impulse.GetNDF()<<"\n";

        std::cout<<"=============\n";

        std::cout<<"Azimuthal angle: \n"<<"Constant: "<<azimuth.GetParameter(0)<<"\n"
            <<"Chi/Dof: "<<azimuth.GetChisquare()/azimuth.GetNDF()<<"\n";

        std::cout<<"=============\n";

        std::cout<<"Polar angle: \n"<<"Constant: "<<polar.GetParameter(0)<<"\n"
                 <<"Chi/Dof: "<<polar.GetChisquare()/polar.GetNDF()<<"\n";

        std::cout<<"=============\n";
    }
}




