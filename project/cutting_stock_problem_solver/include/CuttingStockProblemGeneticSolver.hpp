#pragma once

GABoolean GATerminateUponGenerationOrTime(GAGeneticAlgorithm& geneticAlgorithm){
    static auto algorithmStart = std::chrono::high_resolution_clock::now();
    if (geneticAlgorithm.generation() >= geneticAlgorithm.nGenerations()) return gaTrue;
    if (geneticAlgorithm.generation() % 150 == 0) {
        auto algorithmCheckpoint = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeDifference = algorithmCheckpoint - algorithmStart;
        if (timeDifference.count() > 300) {
            return gaTrue;
        }
    }
    return gaFalse;
}


class CuttingStockProblemGeneticSolver final 
{
public:

    CuttingStockProblemGeneticSolver(double mutationProbability, double crossoverProbability, 
        int populationSize = 1000, int numberOfGenerations = 5000) : 
        mutationProbability(mutationProbability), 
        crossoverProbability(crossoverProbability),
        populationSize(populationSize),
        numberOfGenerations(numberOfGenerations) {}


    CompositeGenome run(int numberOfFiguresToCut, float (*objectiveFunction)(GAGenome& genome)) 
    {
        // Prepare instance of composite genome
        CompositeGenome genome(numberOfFiguresToCut, objectiveFunction);

        // Create and configure simple genetic algorithm instance
        GASteadyStateGA geneticAlgorithm(genome);
        geneticAlgorithm.populationSize(populationSize);
        geneticAlgorithm.nGenerations(numberOfGenerations);
        geneticAlgorithm.pMutation(mutationProbability);
        geneticAlgorithm.pCrossover(crossoverProbability);
        geneticAlgorithm.selector(GARouletteWheelSelector(GASelectionScheme::RAW));
        geneticAlgorithm.scaling(GANoScaling());
        geneticAlgorithm.terminator(GATerminateUponGenerationOrTime);

        // Evolution
        geneticAlgorithm.evolve(static_cast<unsigned>(time(0)));

        // Data about best genome extraction
        CompositeGenome bestGenome(numberOfFiguresToCut, objectiveFunction);
        bestGenome = geneticAlgorithm.statistics().bestIndividual();

        return bestGenome;
    }

private:

    // genetic operations probabilities
    double mutationProbability;
    double crossoverProbability;

    // genetic algorithm properties
    int populationSize;
    int numberOfGenerations;

};