//
// Created by Giacomo Errani on 04/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP

#include "TH1.h"
#include <map>

namespace ResonanceSimulator {
    /**
     * Store datas to be analysed
     * The storage type may vary across different versions
     */
    class particleStorage : public TObject {
    public:
        using histCont = std::map<std::string, TH1F>;
        using hist = TH1F;

        particleStorage() = default;

        static constexpr unsigned invMassBins{100};
        static void makeDefaultHistograms(particleStorage &storage);

        //Histograms classified by type
        //generation histograms
        hist ParticlesType{};
        hist AzimuthalAngles{};
        hist PolarAngles{};
        //dynamics
        hist Impulse{};
        hist TransverseImpulse{};
        hist Energies{};
        //relativistic
        hist InvariantMasses{};
        hist InvariantMassesAlld{};
        hist InvariantMassesAllc{};
        hist InvariantMassesDecayC{}; /// Concordant particles that can be generated as result of decay
        hist InvariantMassesDecayD{}; /// Discordant particles that can be generated as result of decay
        hist InvariantMassesDprod{};

    ClassDefOverride(particleStorage, 1);
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
