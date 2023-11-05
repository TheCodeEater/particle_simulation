//
// Created by Giacomo Errani on 05/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
#define ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP

#include <memory>
#include "TCanvas.h"

namespace BASE_NS{
    /**
     * This enums defines the possible scenes that can be displayed
     */
    enum class Menu{
        mainMenu, /// Choice menu with buttons (lileky won't be implemented)
        generationHistograms, /// Generated data
        kinematicHistograms, /// Pulse and energy
        invMassHistograms, /// InvariantMass
        signalHistograms /// Decayment signals
    };
    /**
     * This class encapsulates graphics for the particle data analysis
     */
    class AnalyzerGraphics{
        using CanvasPtr=std::unique_ptr<TCanvas>;

    public:
        AnalyzerGraphics();

    private:
        Menu fActiveScreen; /// Currently active screen
        CanvasPtr fCanvas; /// Canvas used to show data
    };
}

#endif //ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
