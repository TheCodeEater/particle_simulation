//
// Created by Giacomo Errani on 05/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
#define ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP

#include <memory>
#include <unordered_map>
#include "TCanvas.h"
#include "TList.h"

#include "particleAnalyser.hpp"

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
        using screenDataStorage=std::unordered_map<std::string,TList>;

    public:
        explicit AnalyzerGraphics(std::shared_ptr<dataAnalyser> analyser);

        /**
         * Change currently active screen
         * @param screen the screen to be shown
         */
        void ShowScreen(Menu screen);

    private:
        std::shared_ptr<dataAnalyser> fDataAnalyser; /// Pointer to the object handling analysed data
        std::shared_ptr<SignalResult> fSignalResult;

        Menu fActiveScreen; /// Currently active screen
        CanvasPtr fCanvas; /// Canvas used to show data

        screenDataStorage fGraphicData; /// store graphical objects for each screen
    };
}

#endif //ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
