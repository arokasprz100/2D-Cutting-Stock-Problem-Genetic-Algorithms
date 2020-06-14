#include "SolutionCleaner.hpp"
#include "CompositeGenome.hpp"
#include "ResultValidator.hpp"

#include <tuple>
#include <vector>

void SolutionCleaner::moveAllFiguresTowardsTheOrigin(CompositeGenome& compositeGenome) {

    FigureDimentionsGlobalStorage figures = FigureDimentionsGlobalStorage::instance();
    std::vector<int> indices(figures.getNumberOfFigures());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](int i, int j){ 
        return compositeGenome.xPositions->gene(i) < compositeGenome.xPositions->gene(j); });

    for (auto& i : indices) {
        if (compositeGenome.isUsed->gene(i)) {
            int previousXPosition = compositeGenome.xPositions->gene(i);
            
            compositeGenome.xPositions->gene(i, 0);
            if (!ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i)){
                continue;
            }

            compositeGenome.xPositions->gene(i, previousXPosition);
            for (int j = 0; j < figures.getNumberOfFigures(); ++j) {

                Figure currentFigure(figures.getFigureSize(j), compositeGenome.getByIndex(j));
                int newXPosition = currentFigure.xPosition() + currentFigure.width();
                if (i == j || !compositeGenome.isUsed->gene(j) || newXPosition > previousXPosition) continue;

                compositeGenome.xPositions->gene(i, newXPosition);
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i)) {
                    compositeGenome.xPositions->gene(i, previousXPosition);
                }
                else {
                    previousXPosition = newXPosition;
                }
            }
        }
    }

    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](int i, int j){ 
        return compositeGenome.yPositions->gene(i) < compositeGenome.yPositions->gene(j); });

    for (auto& i : indices) {
        if (compositeGenome.isUsed->gene(i)) {
            int previousYPosition = compositeGenome.yPositions->gene(i);

            compositeGenome.yPositions->gene(i, 0);
            if (!ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i)){
                continue;
            }

            compositeGenome.yPositions->gene(i, previousYPosition);
            for (int j = 0; j < figures.getNumberOfFigures(); ++j) {

                Figure currentFigure(figures.getFigureSize(j), compositeGenome.getByIndex(j));
                int newYPosition = currentFigure.yPosition() + currentFigure.height();
                if (i == j || !compositeGenome.isUsed->gene(j) || newYPosition > previousYPosition) continue;

                compositeGenome.yPositions->gene(i, newYPosition);
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i)) {
                    compositeGenome.yPositions->gene(i, previousYPosition);
                }
                else {
                    previousYPosition = newYPosition;
                }
            }
        }
    }
}


void SolutionCleaner::tryToAddRemainingFigures(CompositeGenome& compositeGenome) {
    FigureDimentionsGlobalStorage figures = FigureDimentionsGlobalStorage::instance();

    for (int x = 0; x < Sheet::width; ++x) {
        for (int y = 0; y < Sheet::height; ++y) {

            for (int i = 0; i < figures.getNumberOfFigures(); ++i) {

                // we skip figures that are already used
                if (compositeGenome.isUsed->gene(i)) continue;

                // reset rotation settings
                compositeGenome.isRotated->gene(i, 0);

                // set coordinates
                compositeGenome.xPositions->gene(i, x);
                compositeGenome.yPositions->gene(i, y);

                // mark as used
                compositeGenome.isUsed->gene(i, 1);

                // check if solution has not been broken - if so, remove the figure
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i) || ResultValidator::checkIfFigureIsOutsideSheet(compositeGenome, figures, i)) {
                    compositeGenome.isUsed->gene(i, 0);
                } 
                else {
                    break;
                }

                compositeGenome.isRotated->gene(i, 1);
                compositeGenome.isUsed->gene(i, 1);

                // check if solution has not been broken - if so, remove the figure
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i) || ResultValidator::checkIfFigureIsOutsideSheet(compositeGenome, figures, i)) {
                    compositeGenome.isUsed->gene(i, 0);
                } 
                else {
                    break;
                }
            }

        }
    }
}


void SolutionCleaner::removeFiguresThatBreakTheSolution(CompositeGenome& compositeGenome) {

    FigureDimentionsGlobalStorage figures = FigureDimentionsGlobalStorage::instance();
    for (int i = 0; i < figures.getNumberOfFigures(); ++i) {

        if (compositeGenome.isUsed->gene(i) == 0) continue;

        // remove figure from solution if it overlaps with other figures
        if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, figures, i)) {
            compositeGenome.isUsed->gene(i, 0);
        }

        // remove figure from solution if part of it lies outside sheet
        if (ResultValidator::checkIfFigureIsOutsideSheet(compositeGenome, figures, i)) {
            compositeGenome.isUsed->gene(i, 0);
        }
    }
}