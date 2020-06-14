#pragma once

#include <utility>
#include <tuple>

class Figure final
{
public:

    Figure(const std::pair<int, int>& figureDimentions, const std::tuple<int, int, int, int>& figurePositionAndRotation) : 
        figureWidth(std::get<3>(figurePositionAndRotation) ? figureDimentions.second : figureDimentions.first),
        figureHeight(std::get<3>(figurePositionAndRotation) ? figureDimentions.first : figureDimentions.second),
        figureXCoord(std::get<0>(figurePositionAndRotation)),
        figureYCoord(std::get<1>(figurePositionAndRotation)),
        isFigureUsed(std::get<2>(figurePositionAndRotation)) {}

    int area() const { return figureWidth * figureHeight; }
    int width() const { return figureWidth; }
    int height() const { return figureHeight; }
    int xPosition() const { return figureXCoord; }
    int yPosition() const { return figureYCoord; }
    bool isUsed() const { return isFigureUsed; }

private:

    int figureWidth;
    int figureHeight;
    int figureXCoord;
    int figureYCoord;
    bool isFigureUsed;
};