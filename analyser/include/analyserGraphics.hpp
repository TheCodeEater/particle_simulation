//
// Created by Giacomo Errani on 05/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
#define ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP

#include <memory>
#include <unordered_map>

#include "TCanvas.h"
#include "TPad.h"

#include "particleAnalyser.hpp"

namespace BASE_NS {
    /**
     * This class encapsulates graphics for the particle data analysis
     */
    class AnalyzerGraphics {
        using CanvasPtr = std::unique_ptr<TCanvas>;
        using CanvasCont = std::unordered_map<std::string,CanvasPtr>;

    public:
        explicit AnalyzerGraphics(dataAnalyser &analyser);

    private:
        std::shared_ptr<particleStorage> fInputData; /// Pointer to the object handling analysed data
        std::shared_ptr<SignalResult> fSignalResult;

        //canvas with resulting histograms, similar with similar       
        /*CanvasPtr MassCanvas;
        CanvasPtr PartTypeCanvas;
        CanvasPtr DistributionsCanvas;
        CanvasPtr SumCanvas;
        CanvasPtr PulseCanvas;*/
        CanvasCont fCanvasContainer;

        void graphicSetup();

        void drawCanvases();

        void writeHistograms() const;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_ANALYSERGRAPHICS_HPP
