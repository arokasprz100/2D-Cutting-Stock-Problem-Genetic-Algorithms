#include "InputDataReader.hpp"
#include "CompositeGenome.hpp"
#include "FigureDimentionsGlobalStorage.hpp"
#include "ResultsWriter.hpp"
#include "Figure.hpp"
#include "SolutionCleaner.hpp"
#include "ObjectiveFunction.hpp"
#include "CuttingStockProblemGeneticSolver.hpp"

#include <iostream>
#include <chrono>



int main() {

    auto figuresDimentions = InputDataReader().fromFile("maleplyty.txt");
    FigureDimentionsGlobalStorage::instance(figuresDimentions);

    auto algorithmStartTime =  std::chrono::steady_clock::now();

    std::cout << "Running genetic algorithm. This may take a while ... " << std::endl << std::endl;
    CuttingStockProblemGeneticSolver cuttingStockProblemGeneticSolver(0.05, 0.75, 1000, 1000);
    CompositeGenome bestGenome = cuttingStockProblemGeneticSolver.run(figuresDimentions.size(), objectiveFunction);
    std::cout << "Best solution returned from genetic algorithm: \n" << bestGenome << std::endl;

    std::cout << "Cleaning the solution. This may take a while ... " << std::endl;
    SolutionCleaner::removeFiguresThatBreakTheSolution(bestGenome);
    SolutionCleaner::moveAllFiguresTowardsTheOrigin(bestGenome);

    auto algorithmFirstPartEndTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeDifference = algorithmFirstPartEndTime - algorithmStartTime;
    if (timeDifference.count() < 120) {
        std::cout << "Improving the solution. This may take a while ... " << std::endl << std::endl;
        SolutionCleaner::tryToAddRemainingFigures(bestGenome);
    }

    std::cout << "Best solution after cleaning: \n" << bestGenome << std::endl;

    std::cout << "Writing to file output.txt ..." << std::endl << std::endl;
    ResultsWriter resultsWriter(bestGenome, FigureDimentionsGlobalStorage::instance());
    resultsWriter.toFile("output.txt");
    resultsWriter.toStandardOutput();

    auto algorithmEndTime = std::chrono::steady_clock::now();
    timeDifference = algorithmEndTime - algorithmStartTime;
    std::cout << "Elapsed time: " << timeDifference.count() << "s" << std::endl;

    return 0;
}

