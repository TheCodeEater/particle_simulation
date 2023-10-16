//
// Created by Giacomo Errani on 10/10/23.
//
#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TRootCanvas.h"

#include <random>

int main(int argc, char** argv) {
    TApplication app("app", &argc, argv);

    gRandom->SetSeed(std::random_device{}()); //generate random seed using hardware

    TCanvas *c = new TCanvas("c", "Something", 0, 0, 800, 600);
        TH1F *h =new TH1F("h","abundancies",5,0,5);
//cosmetics
        h->SetLineColor(1);
        h->GetYaxis()->SetTitleOffset(1.2);
        h->GetXaxis()->SetTitleSize(0.04);
        h->GetYaxis()->SetTitleSize(0.04);
        h->GetXaxis()->SetTitle("Cases");
        h->GetYaxis()->SetTitle("Entries");
        h->SetFillColor(4);
        Double_t x=0;

        for(Int_t i=0;i<1e5;i++){
            x=gRandom->Rndm();
            if(x<0.1)h->Fill(0);
            else if(x<0.3)h->Fill(1);
            else if(x<0.7)h->Fill(2);
            else if(x<0.95)h->Fill(3);
            else h->Fill(4);
        }
        h->SetMinimum(0);
        h->SetFillColor(kGreen);
        h->Draw("HIST");
        h->Draw("PE*,SAME");
    c->Modified(); c->Update();
    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
    return 0;
}