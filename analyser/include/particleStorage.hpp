//
// Created by Giacomo Errani on 04/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP

#include "Definitions.hpp"
#include "TH1.h"
#include <unordered_map>

namespace BASE_NS{
    /**
     * Store datas to be analysed
     * The storage type may vary across different versions
     */
    struct particleStorage: public TObject{
        using histCont=std::unordered_map<std::string,TH1F>;
        using hist=TH1F;

        particleStorage()=default;

        //Histograms classified by type
        hist GeneratedTypes{};
        hist PolarAngles{};
        hist AzimuthAngles{};
        hist Pulse{};
        hist TransPulse{};
        hist Energy{};

        //store all invariant masses histograms into a container
        histCont invMasses{};

        ClassDefInlineOverride(particleStorage,1);
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
