//
// Created by Giacomo Errani on 10/10/23.
//
#include "TApplication.h"
#include "TRint.h"

#include "Definitions.hpp"

int main(int argc, char** argv) {
    //create root application
    APP_TYPE app(APP_NAME, &argc, argv);

    //create the logic objects

    //do stuff

    //run application
    app.Run();
    return 0;
}