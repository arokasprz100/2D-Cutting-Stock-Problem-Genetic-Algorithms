#pragma once

class Pieces 
{
public:

    static Pieces getInstance(std::vector<std::tuple<int, int>> pieceSizes = {}) {
        static Pieces pieces(pieceSizes);
        return pieces;
    }

    const std::tuple<int, int>& getPieceSize(int number) const {
        return pieceSizes.at(number);
    }

    int getNumberOfPieces() const {
        return pieceSizes.size();
    }

private:

    Pieces(std::vector<std::tuple<int, int>> pieceSizes) : pieceSizes(pieceSizes) {}

    std::vector<std::tuple<int, int>> pieceSizes;
};