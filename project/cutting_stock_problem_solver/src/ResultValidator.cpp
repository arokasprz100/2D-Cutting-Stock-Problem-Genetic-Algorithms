#include "ResultValidator.hpp"

bool ResultValidator::checkIfContainsOverlappingFigures(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures) {
    for (int i = 0; i < figures.getNumberOfFigures(); ++i) {
        if (checkIfSingleFigureOverlapsWithOthers(genome, figures, i)) {
            return true;
        }
    }
    return false;
}


bool ResultValidator::checkIfSingleFigureOverlapsWithOthers(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures, int figureIndex) {
    Figure currentFigure(figures.getFigureSize(figureIndex), genome.getByIndex(figureIndex));
    if (!currentFigure.isUsed()) return false;
    for (int i = 0; i < figures.getNumberOfFigures(); ++i) {
        Figure otherFigure (figures.getFigureSize(i), genome.getByIndex(i));
        if (i == figureIndex || !otherFigure.isUsed()) continue;
        if (!(otherFigure.xPosition() >= currentFigure.xPosition() + currentFigure.width() ||
            currentFigure.xPosition() >= otherFigure.xPosition() + otherFigure.width() ||
            otherFigure.yPosition() >= currentFigure.yPosition() + currentFigure.height() ||
            currentFigure.yPosition() >= otherFigure.yPosition() + otherFigure.height())) 
        {
            return true;
        }
    }
    return false;
}


bool ResultValidator::checkIfContainsFiguresOutsideSheet(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures) {
    for (int i = 0; i < figures.getNumberOfFigures(); ++i) {
        if (checkIfFigureIsOutsideSheet(genome, figures, i)) {
            return true;
        }
    }
    return false;
}


bool ResultValidator::checkIfFigureIsOutsideSheet(const CompositeGenome& genome, const FigureDimentionsGlobalStorage& figures, int figureIndex) {
    Figure currentFigure (figures.getFigureSize(figureIndex), genome.getByIndex(figureIndex));
    if (!currentFigure.isUsed()) return false;
    if (currentFigure.width() + currentFigure.xPosition() > Sheet::width || currentFigure.height() + currentFigure.yPosition() > Sheet::height) {
        return true;
    }
    return false;
}