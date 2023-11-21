//
// Created by Giacomo Errani on 05/11/23.
//
#include "Definitions.hpp"

#include "dataStructures/signalFitResult.hpp"

namespace ResonanceSimulator {
    SignalResult::SignalResult(const SignalResult::Hist &signal1, const SignalResult::Hist &signal2,
                               const SignalResult::FitPtr &fitSignal1, const SignalResult::FitPtr &fitSignal2)
            : signal1{signal1}, signal2{signal2}, fitSignal1{fitSignal1}, fitSignal2{fitSignal2} {}
}