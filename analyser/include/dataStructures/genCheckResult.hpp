//
// Created by Giacomo Errani on 05/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_GENCHECKRESULT_HPP
#define ROOT_TEMPLATE_PROJECT_GENCHECKRESULT_HPP

#include "Definitions.hpp"

#include <string>
#include <sstream>

namespace BASE_NS {
    /**
* Represent the result of distribution consistency check
*/
    class CheckResult {

    public:
        CheckResult(bool success, std::string error);

        /**
         * Convert to bool
         * @return fSuccessful
         */
        explicit operator bool() const;

        /**
         * Get error string
         * @return error string
         */
        [[nodiscard]] std::string const &GetError() const;

    private:
        bool fSuccessful{}; /// wether the check was successful
        std::string fError{}; /// Arose errors
    };
}

#endif //ROOT_TEMPLATE_PROJECT_GENCHECKRESULT_HPP
