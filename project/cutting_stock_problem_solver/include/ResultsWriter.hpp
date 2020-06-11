#pragma once

#include "FiguresAreaCalculator.hpp"

#include <sstream>

class ResultsWriter
{
public:

    ResultsWriter(const CompositeGenome& bestGenome, const Pieces& pieces) : bestGenome(bestGenome), pieces(pieces) {}

    void toFile(const std::string& fileName) {
        const std::string result = generateResultsString();
        std::ofstream file(fileName);
        file << result;
    }

    void toStandardOutput() {
        const std::string result = generateResultsString();
        std::cout << result << std::endl;
    }

private:

    std::string generateResultsString() const {
        int figuresArea = FiguresAreaCalculator().calculate(bestGenome, pieces);
        std::stringstream sstream;
        sstream << figuresArea << std::endl;
        for (int i = 0; i < pieces.getNumberOfPieces(); ++i) {
            auto pieceSize = pieces.getPieceSize(i);
            auto pieceGenomeDetails = bestGenome.getByIndex(i);
            sstream << std::get<0>(pieceSize) << " " << std::get<1>(pieceSize) << " ";
            if (std::get<2>(pieceGenomeDetails)) {
                sstream << std::get<0>(pieceGenomeDetails) << " " << std::get<1>(pieceGenomeDetails) << " ";
            }
            else {
                sstream << "-1 -1 "; 
            }
            sstream << std::get<3>(pieceGenomeDetails) << std::endl;
        }
        return sstream.str();
    }


    CompositeGenome bestGenome;
    Pieces pieces;

};