#pragma once

#include "AreaCalculating.hpp"
#include "Piece.hpp"

class OverlappingAreaCalculator final : public AreaCalculating
{
public:

    int calculate(const CompositeGenome& genome, const Pieces& pieces) const override {

        int totalArea = 0;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {

            Piece currentPiece (pieces.getPieceSize(i), genome.getByIndex(i));

            // if this figure is not used, we can skip it - it does not matter if it 
            // overlaps anything or not
            if (!currentPiece.isUsed()) continue;

            for (int j = 0; j < pieces.getNumberOfPieces(); ++j) {

                // if this is the same figure as current, we skip
                if (i == j) continue;

                Piece otherPiece (pieces.getPieceSize(j), genome.getByIndex(j));

                // again, if this figure is not used, we can skip it
                if (!otherPiece.isUsed()) continue;

                // add to total overlapping area
                totalArea += calculateOverlappingAreaOfTwoRectangles(currentPiece, otherPiece);
            }

        }
        // we divide by two, because every overlapping area has been calculated twice
        return totalArea / 2;
    }

private:

    // Source:
    // http://jsfiddle.net/Lqh3mjr5/
    // https://math.stackexchange.com/questions/99565/simplest-way-to-calculate-the-intersect-area-of-two-rectangles
    int calculateOverlappingAreaOfTwoRectangles(const Piece& pieceA, const Piece& pieceB) const {
        int pieceARightXPosition = pieceA.xPosition() + pieceA.width();
        int pieceABottomYPosition = pieceA.yPosition() + pieceA.height();

        int pieceBRightXPosition = pieceB.xPosition() + pieceB.width();
        int pieceBBottomYPosition = pieceB.yPosition() + pieceB.height();

        int xOverlap = std::max(0, std::min(pieceARightXPosition, pieceBRightXPosition) - std::max(pieceA.xPosition(), pieceB.xPosition()));
        int yOverlap = std::max(0, std::min(pieceABottomYPosition, pieceBBottomYPosition) - std::max(pieceA.yPosition(), pieceB.yPosition()));
        return xOverlap * yOverlap;
    }

};