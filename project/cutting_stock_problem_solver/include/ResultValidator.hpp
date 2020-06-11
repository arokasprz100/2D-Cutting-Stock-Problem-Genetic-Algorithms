#pragma once

#include "Piece.hpp"
#include "Pieces.hpp"
#include "CompositeGenome.hpp"

class ResultValidator final
{
public:

    static bool checkIfContainsOverlappingFigures(const CompositeGenome& genome, const Pieces& pieces) {
        bool containsOverlappingFigures = false;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {
            if (checkIfSingleFigureOverlapsWithOthers(genome, pieces, i)) {
                containsOverlappingFigures = true;
                break;
            }
        }
        return containsOverlappingFigures;
    }


    static bool checkIfSingleFigureOverlapsWithOthers(const CompositeGenome& genome, const Pieces& pieces, int figureIndex) {

        bool overlapsWithOtherFigure = false;
        Piece currentPiece(pieces.getPieceSize(figureIndex), genome.getByIndex(figureIndex));

        if (!currentPiece.isUsed()) return overlapsWithOtherFigure;

        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {

            Piece otherPiece (pieces.getPieceSize(i), genome.getByIndex(i));
            if (i == figureIndex || !otherPiece.isUsed()) continue;

            if (!(otherPiece.xPosition() >= currentPiece.xPosition() + currentPiece.width() ||
                currentPiece.xPosition() >= otherPiece.xPosition() + otherPiece.width() ||
                otherPiece.yPosition() >= currentPiece.yPosition() + currentPiece.height() ||
                currentPiece.yPosition() >= otherPiece.yPosition() + otherPiece.height())) 
            {
                overlapsWithOtherFigure = true;
                break;
            }

        }
        return overlapsWithOtherFigure;
    }


    static bool checkIfContainsFiguresOutsideSheet(const CompositeGenome& genome, const Pieces& pieces) {

        // get sheet size from algorithm settings
        int sheetWidth = AlgorithmSettings::xPositionUpperBound;
        int sheetHeight = AlgorithmSettings::yPositionUpperBound;

        // iterate over figures and set flag 
        bool isThereFigureOutsideSheet = false;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {

            // get data about currently processed figure
            Piece currentPiece (pieces.getPieceSize(i), genome.getByIndex(i));
            int rightEdgeXPosition = currentPiece.width() + currentPiece.xPosition();
            int lowerEdgeYPosition = currentPiece.height() + currentPiece.yPosition();

            // if current figure is not used, we do not check it
            if (!currentPiece.isUsed()) continue;

            // check if any part of the figure lies outside sheet
            if (rightEdgeXPosition > sheetWidth || lowerEdgeYPosition > sheetHeight) {
                isThereFigureOutsideSheet = true;
                break;
            }
        }
        return isThereFigureOutsideSheet;
    }

};