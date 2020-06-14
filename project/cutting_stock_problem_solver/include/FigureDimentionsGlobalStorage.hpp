#pragma once

#include <vector>
#include <utility>

class FigureDimentionsGlobalStorage
{
public:

    static FigureDimentionsGlobalStorage instance(std::vector<std::pair<int, int>> figuresDimentions = {}) {
        static FigureDimentionsGlobalStorage figuresDimentionsWrapper(figuresDimentions);
        return figuresDimentionsWrapper;
    }

    std::pair<int, int> getFigureSize(int figureIndex) const { return figuresDimentions.at(figureIndex); }
    int getNumberOfFigures() const { return figuresDimentions.size(); }

private:

    FigureDimentionsGlobalStorage(std::vector<std::pair<int, int>> figuresDimentions) : 
        figuresDimentions(figuresDimentions) {}

    std::vector<std::pair<int, int>> figuresDimentions;
};