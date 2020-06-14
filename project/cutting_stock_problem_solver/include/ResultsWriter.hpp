#pragma once

#include "FiguresAreaCalculator.hpp"

#include <sstream>

class ResultsWriter
{
public:

    ResultsWriter(const CompositeGenome& bestGenome, const FigureDimentionsGlobalStorage& figures) : 
        bestGenome(bestGenome), 
        figures(figures) {}

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
        int figuresArea = FiguresAreaCalculator().calculate(bestGenome, figures);
        std::stringstream sstream;
        sstream << figuresArea << std::endl;
        for (int i = 0; i < figures.getNumberOfFigures(); ++i) {
            auto figureSize = figures.getFigureSize(i);
            auto figureGenomeDetails = bestGenome.getByIndex(i);
            sstream << std::get<0>(figureSize) << " " << std::get<1>(figureSize) << " ";
            if (std::get<2>(figureGenomeDetails)) {
                sstream << std::get<0>(figureGenomeDetails) << " " << std::get<1>(figureGenomeDetails) << " ";
            }
            else {
                sstream << "-1 -1 "; 
            }
            sstream << std::get<3>(figureGenomeDetails) << std::endl;
        }
        return sstream.str();
    }


    CompositeGenome bestGenome;
    FigureDimentionsGlobalStorage figures;

};