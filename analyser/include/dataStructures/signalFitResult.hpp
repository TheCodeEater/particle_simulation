//
// Created by Giacomo Errani on 05/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_SIGNALFITRESULT_HPP
#define ROOT_TEMPLATE_PROJECT_SIGNALFITRESULT_HPP

#include "TH1.h"
#include "TFitResultPtr.h"
#include "TF1.h"

#include <memory>

namespace ResonanceSimulator {
    /**
 * Struct to hold the result of the required histogram difference
 */
    struct SignalResult {
        using Hist = TH1F;
        using FitPtr = TF1;

        SignalResult(const Hist &signal1, const Hist &signal2, const FitPtr &fitSignal1, const FitPtr &fitSignal2,
                     const FitPtr &fitSignal3);

        Hist signal1; /// Difference between the 2 kaon-pion histograms
        Hist signal2; /// Difference between the concordant and discordant charge histogram
        FitPtr fitSignal1; /// Fit result ptr for signal 1
        FitPtr fitSignal2; /// Fit result ptr for signal 2
        FitPtr fitSignal3; /// Fit result for direct child histogram


    };

}

#endif //ROOT_TEMPLATE_PROJECT_SIGNALFITRESULT_HPP
