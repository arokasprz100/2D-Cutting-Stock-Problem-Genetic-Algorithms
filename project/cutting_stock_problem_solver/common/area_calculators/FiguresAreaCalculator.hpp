#pragma once

#include "AreaCalculating.hpp"
#include "Piece.hpp"

class FiguresAreaCalculator final : public AreaCalculating
{
public:

    int calculate(const CompositeGenome& genome, const Pieces& pieces) const override {

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