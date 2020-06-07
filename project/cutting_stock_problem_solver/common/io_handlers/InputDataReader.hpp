#pragma once

#include <vector>
#include <tuple>
#include <fstream>

class InputDataReader
{
public:


    std::vector<std::tuple<int, int>> fromFile(const std::string& fileName) {
        std::ifstream inputFile(fileName);

        std::vector<std::tuple<int, int>> pieceSizes;
        int width = 0, height = 0;
        while (inputFile >> width >> height) {
            pieceSizes.emplace_back(width, height);
        }
        return pieceSizes;
    }

private:

};