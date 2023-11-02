//
// Created by Giacomo Errani on 02/11/23.
//
#include "particleAnalyser.hpp"
#include "Definitions.hpp"

#include "TKey.h"

namespace BASE_NS{

    dataAnalyser::dataAnalyser(const std::string &path):
        //open the root file in read only mode
        fFile{new TFile{path.c_str(),"READ"}},
        //create empty TList
        fList{}{

        //check that the file was opened correctly
        if(fFile->IsOpen()){
            throw std::runtime_error{"Cannot open root file. Path: "+path};
        }

        //populate the list from tfile
        //get the TList
        const TList* histoList{dynamic_cast<TList*>(fFile->Get("particles_decay_data"))};

        //if the list does not exist or it is not the correct type, throw
        if(histoList== nullptr){
            throw std::bad_cast{};
        }
        //populate map
        std::for_each(histoList->begin(),histoList->end(),[](auto object){
            auto histo=dynamic_cast<TH1F*>(object);
            if(histo== nullptr){
                throw std::bad_cast{};
            }
            return std::pair<std::string,TH1F*>{histo->GetName(),histo};
        });
    }

    TFile const &dataAnalyser::GetFile() const {
        //check wether file is valid using unique_ptr bool conversion operator
        if(!fFile){
            throw std::runtime_error{"Root file object is invalid!"};
        }
        return *fFile;
    }
}