//
// Created by Giacomo Errani on 12/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_APPLICATION_HPP
#define ROOT_TEMPLATE_PROJECT_APPLICATION_HPP

#include "Definitions.hpp"

#include "TApplication.h"
#include "TRootCanvas.h"

namespace BASE_NS{
    /**
     * Class to represent the root application itself
     */
    class Application{

    public:
    private:
        TApplication app_;
    };
}

#endif //ROOT_TEMPLATE_PROJECT_APPLICATION_HPP
