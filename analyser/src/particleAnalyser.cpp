//
// Created by Giacomo Errani on 02/11/23.
//
#include "particleAnalyser.hpp"
#include "Definitions.hpp"

namespace BASE_NS{

    dataAnalyser::dataAnalyser(const std::string &path):
        //open the root file in read only mode
        fFile{new TFile{path.c_str(),"READ"}}{

        //check that the file was opened correctly
        if(fFile->IsZombie()){
            throw std::runtime_error{"Cannot open root file. Path: "+path};
        }
    }

    TFile const &dataAnalyser::getFile() const {
        //check wether file is valid using unique_ptr bool conversion operator
        if(!fFile){
            throw std::runtime_error{"Root file object is invalid!"};
        }
        return *fFile;
    }
}