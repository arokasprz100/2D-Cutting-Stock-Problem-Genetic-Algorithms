#pragma once

#include "FiguresAreaCalculator.hpp"
#include "ResultValidator.hpp"

float objectiveFunction(GAGenome& genome) {

    float maxArea = AlgorithmSettings::xPositionUpperBound * AlgorithmSettings::yPositionUpperBound;

    CompositeGenome& compositeGenome = dynamic_cast<CompositeGenome&>(genome);
    Pieces pieces = Pieces::getInstance();

    return static_cast<float>( ResultValidator::checkIfContainsOverlappingFigures(compositeGenome, pieces) 
        || ResultValidator::checkIfContainsFiguresOutsideSheet(compositeGenome, pieces) 
        ? 0 : FiguresAreaCalculator::calculate(compositeGenome, pieces) ) / maxArea;
}
