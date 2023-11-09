//
// Created by Giacomo Errani on 23/10/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_LINKDEF_H
#define ROOT_TEMPLATE_PROJECT_LINKDEF_H

#include "Definitions.hpp"

#ifdef __CLING__
#pragma link C++ nestedclasses; //link nested classes
#pragma link C++ nestedtypedefs; //link nested typedefs
#pragma link C++ class ResonanceSimulator::particleStorage+;
//#pragma link C++ class MyClass; link myClass
#endif

#endif //ROOT_TEMPLATE_PROJECT_LINKDEF_H
