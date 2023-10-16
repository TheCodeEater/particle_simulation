//
// Created by Giacomo Errani on 10/10/23.
//
#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TRint.h"
#include "TRootCanvas.h"

#include "Definitions.hpp"

#include <random>

int main(int argc, char** argv) {
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects

    //do stuff

    //run application
    app.Run();
    return 0;
}