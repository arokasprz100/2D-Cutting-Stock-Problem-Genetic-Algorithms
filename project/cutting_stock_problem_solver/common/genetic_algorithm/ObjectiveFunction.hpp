#pragma once

#include "FiguresAreaCalculator.hpp"
#include "OverlappingAreaCalculator.hpp"
#include "AreaOutsideSheetCalculator.hpp"

#include <cmath>

// TODO: test
float objectiveFunction(GAGenome& genome) {
    CompositeGenome& complexGenome = static_cast<CompositeGenome&>(genome);
    Pieces pieces = Pieces::getInstance();

    int figuresArea = FiguresAreaCalculator().calculate(complexGenome, pieces);
    int areaOutsideSheet = AreaOutsideSheetCalculator().calculate(complexGenome, pieces);
    int overlappingArea = OverlappingAreaCalculator().calculate(complexGenome, pieces); 
    
    int penaltyValue = std::pow(areaOutsideSheet, 2) + std::pow(overlappingArea, 2);
    return (figuresArea - penaltyValue > 0 ? figuresArea - penaltyValue : 0);
}
