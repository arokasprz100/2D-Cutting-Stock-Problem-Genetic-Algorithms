#pragma once

#include "Figure.hpp"
#include "FigureDimentionsGlobalStorage.hpp"
#include "CompositeGenome.hpp"

class ResultValidator final
{
public:

    static bool checkIfContainsOverlappingFigures(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures);
    static bool checkIfSingleFigureOverlapsWithOthers(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures, int figureIndex);
    static bool checkIfContainsFiguresOutsideSheet(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures);
    static bool checkIfFigureIsOutsideSheet(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures, int figureIndex);
};