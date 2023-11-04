//
// Created by Giacomo Errani on 04/11/23.
//
#include "particleStorage.hpp"

#include "Rtypes.h"

namespace BASE_NS{
    particleStorage::particleStorage() {
        //generate data structures for histogram error calculation
        for(auto & node: invMasses){
            node.second.Sumw2();
        }
    }
    //ClassImp(particleStorage);
}