#include "InputDataReader.hpp"
#include "CompositeGenome.hpp"
#include "Pieces.hpp"
#include "ResultsWriter.hpp"
#include "Piece.hpp"
#include "ObjectiveFunction.hpp"

#include "CuttingStockProblemGeneticSolver.hpp"

#include <ga/ga.h>
#include <iostream>
#include <chrono>



int main() {

    InputDataReader inputDataReader;
    auto pieceSizes = inputDataReader.fromFile("maleplyty.txt");

    Pieces::getInstance(pieceSizes);

    auto algorithmStartTime =  std::chrono::steady_clock::now();

    CuttingStockProblemGeneticSolver cuttingStockProblemGeneticSolver(0.05, 0.5, 1000, 1000);
    CompositeGenome bestGenome = cuttingStockProblemGeneticSolver.run(pieceSizes.size(), objectiveFunction);
    std::cout << "Best solution: \n" << bestGenome << std::endl << std::endl;

    ResultsWriter resultsWriter(bestGenome, Pieces::getInstance());
    resultsWriter.toFile("output.txt");
    resultsWriter.toStandardOutput();

    auto algorithmEndTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeDifference = algorithmEndTime - algorithmStartTime;
    std::cout << "Elapsed time: " << timeDifference.count() << "s" << std::endl;

    return 0;
}

