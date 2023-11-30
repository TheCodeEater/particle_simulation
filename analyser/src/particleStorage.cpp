//
// Created by Giacomo Errani on 04/11/23.
//
#include "particleStorage.hpp"
#include "TMath.h"

namespace ResonanceSimulator {
    /*particleStorage::particleStorage() {
        //generate data structures for histogram error calculation
        for(auto & node: invMasses){
            node.second.Sumw2();
        }
    }*/
    void particleStorage::makeDefaultHistograms(particleStorage &storage) {
        storage.ParticlesType = TH1F("ParticlesType", "Particles Type", 7, 0, 7);
        storage.AzimuthalAngles = TH1F("AzimuthalAngles", "Azimuthal Angles", 100, 0, 2 * TMath::Pi());
        storage.PolarAngles = TH1F("PolarAngles", "Polar Angles", 100, 0, TMath::Pi());
        storage.Impulse = TH1F("Impulse", "Impulse", 100, 0, 5);
        storage.TransverseImpulse = TH1F("TransverseImpulse", "Transverse Impulse", 100, 0, 5);
        storage.Energies = TH1F("Energies", "Energies", 100, 0, 10);
        storage.InvariantMasses = TH1F("InvariantMasses", "Invariant Masses", 100, 0, 10);
        storage.InvariantMasses.Sumw2(); //enable error prorpagation structures
        storage.InvariantMassesAlld = TH1F("InvariantMassesAlld", "Invariant Masses Alld", invMassBins, 0, 10);
        storage.InvariantMassesAllc = TH1F("InvariantMassesAllc", "Invariant Masses Allc", invMassBins, 0, 10);
        storage.InvariantMassesDecayC = TH1F("InvariantMassesDecayC", "Invariant Masses Concordant", invMassBins, 0, 10);
        storage.InvariantMassesDecayD = TH1F("InvariantMassesDecayD", "Invariant Masses Discordant", invMassBins, 0, 10);
        storage.InvariantMassesDprod = TH1F("InvariantMassesDprod", "Invariant Masses Dprod", invMassBins, 0, 10);
    }
}