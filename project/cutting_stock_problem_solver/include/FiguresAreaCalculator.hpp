#pragma once

#include "Piece.hpp"

class FiguresAreaCalculator final
{
public:

    static int calculate(const CompositeGenome& genome, const Pieces& pieces) {

        int totalArea = 0;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {
            auto currentPieceSize = pieces.getPieceSize(i);
            auto currentPieceGenomeProperties = genome.getByIndex(i);
            Piece currentPiece (currentPieceSize, currentPieceGenomeProperties);

            totalArea += (currentPiece.isUsed() ? currentPiece.area() : 0);
        }
        return totalArea;
    }

};