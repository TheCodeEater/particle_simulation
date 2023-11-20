//
// Created by Giacomo Errani on 04/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP

#include "Definitions.hpp"
#include "TH1.h"
#include <map>

namespace BASE_NS{
    /**
     * Store datas to be analysed
     * The storage type may vary across different versions
     */
    class particleStorage: public TObject{
    public:
        using histCont=std::map<std::string,TH1F>;
        using hist=TH1F;

        particleStorage()=default;

        static void makeDefaultHistograms(particleStorage& storage);

        //Histograms classified by type
        hist ParticlesType{};
        hist AzimuthalAngles{};
        hist PolarAngles{};
        hist Impulse{};
        hist TransverseImpulse{};
        hist Energies{};
        hist InvariantMasses{};
        hist InvariantMassesAlld{};
        hist InvariantMassesAllc{};
        /*hist InvariantMassesPipKn{};
        hist InvariantMassesPinKp{};
        hist InvariantMassesPipKp{};
        hist InvariantMassesPinKn{};*/
        hist InvariantMassesDecayC{}; /// Concordant particles that can be generated as result of decay
        hist InvariantMassesDecayD{}; /// Discordant particles that can be generated as result of decay
        hist InvariantMassesDprod{};

        ClassDefOverride(particleStorage,1);
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
