#pragma once

#include "AreaCalculating.hpp"
#include "AlgorithmSettings.hpp"
#include "Piece.hpp"

class AreaOutsideSheetCalculator final : public AreaCalculating
{
public:

    AreaOutsideSheetCalculator() : 
        sheetWidth(AlgorithmSettings::xPositionUpperBound), 
        sheetHeight(AlgorithmSettings::yPositionUpperBound) {}

    int calculate(const CompositeGenome& genome, const Pieces& pieces) const override {
        int totalArea = 0;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {
            Piece currentPiece (pieces.getPieceSize(i), genome.getByIndex(i));
            if (!currentPiece.isUsed()) continue;
            totalArea += calculateAreaOutsideSheetForSingleRectangle(currentPiece);
        }
        return totalArea;
    }

private:

    int sheetWidth;
    int sheetHeight;

    int calculateAreaOutsideSheetForSingleRectangle(const Piece& piece) const {
        int rightEdgeXPosition = piece.width() + piece.xPosition();
        int lowerEdgeYPosition = piece.height() + piece.yPosition();
        return  (rightEdgeXPosition > sheetWidth ? piece.height() * (rightEdgeXPosition - sheetWidth) : 0) +    // area on the right
                (lowerEdgeYPosition > sheetHeight ? piece.width() * (lowerEdgeYPosition - sheetHeight) : 0) +   // area on the bottom
                ( (rightEdgeXPosition > sheetWidth && lowerEdgeYPosition > sheetHeight) 
                    ? (rightEdgeXPosition - sheetWidth) * (lowerEdgeYPosition - sheetHeight) : 0);              // area both on right and on the bottom
    }
};