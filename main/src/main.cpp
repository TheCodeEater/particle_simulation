//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"

#include "Definitions.hpp"

int main(int argc, char** argv) {
    //object ownership setup
    #ifdef PROGRAM_USE_LOCAL_OWNERSHIP
    TH1::AddDirectory(false);
    TH2::AddDirectory(false);
    TH3::AddDirectory(false);
    //TTree::AddDirectory(kFalse);
    #endif
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects

    //do stuff

    //run application
    app.Run();
    return 0;
}