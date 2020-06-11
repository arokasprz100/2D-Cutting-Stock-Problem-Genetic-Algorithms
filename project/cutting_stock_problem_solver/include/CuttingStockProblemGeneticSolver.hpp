#pragma once

class CuttingStockProblemGeneticSolver
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
        geneticAlgorithm.selector(GARouletteWheelSelector(GASelectionScheme::RAW));
        geneticAlgorithm.scaling(GANoScaling());

        // Genetic algorithm output configuration
        // geneticAlgorithm.scoreFilename("zbieznosc.dat");
        // geneticAlgorithm.scoreFrequency(10);
        // geneticAlgorithm.flushFrequency(50);

        // Evolution
        // TODO: add better random number generator
        int stepNumber = 0;
        geneticAlgorithm.initialize(static_cast<unsigned>(time(0)));
        while (!geneticAlgorithm.done()) {
            geneticAlgorithm.step();
            std::cout << stepNumber++ << std::endl;
        }
        // geneticAlgorithm.evolve(static_cast<unsigned>(time(0)));

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