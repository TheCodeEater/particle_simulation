//
// Created by Giacomo Errani on 02/11/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "particleAnalyser.hpp"
#include "analyserGraphics.hpp"
#include "TF1.h"
#include "TStyle.h"
#include "TROOT.h"
#include <iostream>

#include "Definitions.hpp"

int main(int argc, char **argv) {    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects
    ResonanceSimulator::dataAnalyser Anal("Particle.root");

    gStyle->SetHistFillColor(kGreen);
    gStyle->SetHistLineColor(kRed);
    gStyle->SetOptStat(1110);
    gStyle->SetOptFit(111);
    gROOT->ForceStyle(true);
    //per avere il numero di ingressi di un istogramma
    /*std::cout << Anal.GetData()->ParticlesType.GetEntries();
    //per avere numero di un certo tipo di particella e relativa incertezza
    std::cout << Anal.GetData()->ParticlesType.GetBinContent(0) << "+/-" << Anal.GetData()->ParticlesType.GetBinError(0);

    TF1 *polarFit = new TF1("PolarFit", "[0]", 0, M_PI);
    TF1 *azimFit = new TF1("AzimFit", "[0]", 0, 2*M_PI);
    polarFit->SetParLimits(0, 0, M_PI);
    azimFit->SetParLimits(0, 0, 2*M_PI);
    Anal.GetData()->PolarAngles.Fit(polarFit);
    Anal.GetData()->AzimuthalAngles.Fit(azimFit);
    //stampa valore dei parametri, chi quadro ridotto e probabilità del fit
    std::cout << "Polar, Param: "<< polarFit->GetParameter(0) << "chi quadro ridotto: " << polarFit->GetChisquare()/polarFit->GetNDF() << "Probabilità: "<<polarFit->GetProb();
    std::cout << "Azimuthal, Param: "<< azimFit->GetParameter(0) << "chi quadro ridotto: " << azimFit->GetChisquare()/azimFit->GetNDF() << "Probabilità: "<<azimFit->GetProb();

    TF1 *impFit = new TF1("ImpFit", "expo(x, [0..1])", 0, 5);
    impFit->SetParameter(0,1);
    impFit->SetParameter(1,1);

    Anal.GetData()->Impulse.Fit(impFit);
    std::cout << "Pulse, Param: " << impFit->GetParameter(0) << " " << impFit->GetParameter(1) << "CQR: " << impFit->GetChisquare()/impFit->GetNDF() << "Probabilità: " << impFit->GetProb();*/
    //graphic setup
    //do stuff
    ResonanceSimulator::AnalyzerGraphics g{Anal};

    //draw all canvases
    g.drawCanvases();

    //notify that canvas have been drawn
    g.graphicSetup();

    //write histograms to file
    g.writeHistograms();

    g.PrintFitResult();

    //run application
    app.Run();
    return 0;
}