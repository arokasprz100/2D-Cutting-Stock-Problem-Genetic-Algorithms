#include "SolutionCleaner.hpp"
#include "CompositeGenome.hpp"
#include "ResultValidator.hpp"

#include <tuple>
#include <vector>

void SolutionCleaner::moveAllFiguresTowardsTheOrigin(CompositeGenome& compositeGenome){

    Pieces pieces = Pieces::getInstance();
    std::vector<int> indices(pieces.getNumberOfPieces());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](int i, int j){ 
        return compositeGenome.xPositions->gene(i) < compositeGenome.xPositions->gene(j); });

    std::vector<int> indicesSortedAccordingToRightEdge(pieces.getNumberOfPieces());
    std::iota(indicesSortedAccordingToRightEdge.begin(), indicesSortedAccordingToRightEdge.end(), 0);

    for (auto& i : indices) {
        if (compositeGenome.isUsed->gene(i)) {

            int previousXPosition = compositeGenome.xPositions->gene(i);
            compositeGenome.xPositions->gene(i, 0);
            if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, pieces, i)){
                compositeGenome.xPositions->gene(i, previousXPosition);
            }
            else {
                continue;
            }

            for (auto& j : indicesSortedAccordingToRightEdge) {

                Piece currentFigure(pieces.getPieceSize(j), compositeGenome.getByIndex(j));
                int newXPosition = currentFigure.xPosition() + currentFigure.width();
                if (i == j || !compositeGenome.isUsed->gene(j) || newXPosition > previousXPosition) continue;

                compositeGenome.xPositions->gene(i, newXPosition);
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, pieces, i)) {
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

    std::vector<int> indicesSortedAccordingToBottomEdge(pieces.getNumberOfPieces());
    std::iota(indicesSortedAccordingToBottomEdge.begin(), indicesSortedAccordingToBottomEdge.end(), 0);

    for (auto& i : indices) {
        if (compositeGenome.isUsed->gene(i)) {

            int previousYPosition = compositeGenome.yPositions->gene(i);
            compositeGenome.yPositions->gene(i, 0);
            if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, pieces, i)){
                compositeGenome.yPositions->gene(i, previousYPosition);
            }
            else {
                continue;
            }

            for (auto& j : indicesSortedAccordingToBottomEdge) {


                Piece currentFigure(pieces.getPieceSize(j), compositeGenome.getByIndex(j));
                int newYPosition = currentFigure.yPosition() + currentFigure.height();
                if (i == j || !compositeGenome.isUsed->gene(j) || newYPosition > previousYPosition) continue;

                compositeGenome.yPositions->gene(i, newYPosition);
                if (ResultValidator::checkIfSingleFigureOverlapsWithOthers(compositeGenome, pieces, i)) {
                    compositeGenome.yPositions->gene(i, previousYPosition);
                }
                else {
                    previousYPosition = newYPosition;
                }

            }
        }
    }
}
