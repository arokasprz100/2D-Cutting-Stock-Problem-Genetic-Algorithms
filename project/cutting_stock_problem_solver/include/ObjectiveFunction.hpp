#pragma once

#include "FiguresAreaCalculator.hpp"
#include "ResultValidator.hpp"

float objectiveFunction(GAGenome& genome) {

    CompositeGenome& compositeGenome = dynamic_cast<CompositeGenome&>(genome);
    FigureDimentionsGlobalStorage figures = FigureDimentionsGlobalStorage::instance();

    // we return 0 if there are any overlapping figures
    if (ResultValidator::checkIfContainsOverlappingFigures(compositeGenome, figures)) {
        return 0;
    }

    // we return 0 if there are any figures outside sheet
    if (ResultValidator::checkIfContainsFiguresOutsideSheet(compositeGenome, figures)) {
        return 0;
    }

    return static_cast<float>(FiguresAreaCalculator::calculate(compositeGenome, figures)) / static_cast<float>(Sheet::area());
}
