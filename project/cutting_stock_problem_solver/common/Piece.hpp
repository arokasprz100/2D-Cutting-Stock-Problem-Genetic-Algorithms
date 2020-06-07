#pragma once

class Piece final
{
public:

    Piece(const std::tuple<int, int>& pieceSize, const std::tuple<int, int, int, int>& pieceGenomeInfo) {
        // We swap sizes if piece is rotated
        pieceWidth = std::get<3>(pieceGenomeInfo) ? std::get<1>(pieceSize) : std::get<0>(pieceSize);
        pieceHeight = std::get<3>(pieceGenomeInfo) ? std::get<0>(pieceSize) : std::get<1>(pieceSize);
        isPieceUsed = (std::get<2>(pieceGenomeInfo) > 0);
        pieceXPosition = std::get<0>(pieceGenomeInfo);
        pieceYPosition = std::get<1>(pieceGenomeInfo);
    }

    int area() const {
        return pieceWidth * pieceHeight;
    }

    int width() const {
        return pieceWidth;
    }

    int height() const {
        return pieceHeight;
    }

    bool isUsed() const {
        return isPieceUsed;
    }

    int xPosition() const {
        return pieceXPosition;
    }

    int yPosition() const {
        return pieceYPosition;
    }

private:

    // TODO: remove piece from names
    int pieceWidth;
    int pieceHeight;
    bool isPieceUsed;
    int pieceXPosition;
    int pieceYPosition;
};