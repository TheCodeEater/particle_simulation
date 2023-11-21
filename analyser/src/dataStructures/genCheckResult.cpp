//
// Created by Giacomo Errani on 05/11/23.
//
#include "Definitions.hpp"
#include "dataStructures/genCheckResult.hpp"

#include <string>

namespace ResonanceSimulator {
    CheckResult::operator bool() const {
        return fSuccessful;
    }

    std::string const &CheckResult::GetError() const {
        return fError;
    }

    CheckResult::CheckResult(bool success, std::string error) :
            fSuccessful{success},
            fError{std::move(error)} {

    }
}