//
// Created by Giacomo Errani on 04/11/23.
//
#include "ParticleStorage.hpp"
#include "TMath.h"

namespace ResonanceSimulator {
    /*ParticleStorage::ParticleStorage() {
        //generate data structures for histogram error calculation
        for(auto & node: invMasses){
            node.second.Sumw2();
        }
    }*/
    void ParticleStorage::makeDefaultHistograms(ParticleStorage &storage) {
        storage.ParticlesType = TH1F("ParticlesType", "Particles Type; Type; Occurrencies", 7, 0, 7);
        storage.AzimuthalAngles = TH1F("AzimuthalAngles", "Azimuthal Angles; Angle (rad); Occurrencies", 100, 0, 2 * TMath::Pi());
        storage.PolarAngles = TH1F("PolarAngles", "Polar Angles; Angle (rad); Occurrencies", 100, 0, TMath::Pi());
        storage.Impulse = TH1F("Impulse", "Impulse; Impulse; Occurrencies", 100, 0, 5);
        storage.TransverseImpulse = TH1F("TransverseImpulse", "Transverse Impulse; Impulse; Occurencies", 100, 0, 5);
        storage.Energies = TH1F("Energies", "Energies; Energy (GeV); Occurrencies", 100, 0, 10);
        storage.InvariantMasses = TH1F("InvariantMasses", "Invariant Masses; Mass (GeV/c2); Occurencies", 100, 0, 10);

        storage.InvariantMassesAlld = TH1F("InvariantMassesAlld", "All discordant charges; Mass (GeV/c2); Occurencies", invMassBins, 0, 10);
        storage.InvariantMassesAllc = TH1F("InvariantMassesAllc", "All concordant charges; Mass (GeV/c2); Occurencies", invMassBins, 0, 10);
        storage.InvariantMassesDecayC = TH1F("InvariantMassesDecayC", "Pion/Kaon concordant charges; Mass (GeV/c2); Occurencies", invMassBins, 0, 10);
        storage.InvariantMassesDecayD = TH1F("InvariantMassesDecayD", "Pion/Kaon discordant charges; Mass (GeV/c2); Occurencies", invMassBins, 0, 10);
        storage.InvariantMassesDprod = TH1F("InvariantMassesDprod", "K* child couples; Mass (GeV/c2); Occurencies", invMassBins, 0, 10);

        //enable error propagation for histograms
        storage.InvariantMassesAlld.Sumw2();
        storage.InvariantMassesAllc.Sumw2();
        storage.InvariantMassesDecayC.Sumw2();
        storage.InvariantMassesDecayD.Sumw2();
    }
}