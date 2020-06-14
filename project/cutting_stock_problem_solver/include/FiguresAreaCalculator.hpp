#pragma once

#include "Figure.hpp"

class FiguresAreaCalculator final
{
public:

    static int calculate(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures) {

        int totalArea = 0;
        for (int i = 0; i < figures.getNumberOfFigures(); ++i) {
            auto currentFigureSize = figures.getFigureSize(i);
            auto currentFigureGenomeProperties = genome.getByIndex(i);
            Figure currentFigure (currentFigureSize, currentFigureGenomeProperties);

            totalArea += (currentFigure.isUsed() ? currentFigure.area() : 0);
        }
        return totalArea;
    }

};