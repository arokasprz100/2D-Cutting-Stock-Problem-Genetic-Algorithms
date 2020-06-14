#include "CompositeGenome.hpp"
#include "InputDataReader.hpp"
#include "FigureDimentionsGlobalStorage.hpp"
#include "ObjectiveFunction.hpp"

#include <iostream>
#include <memory>

int main() {

    // Read figures data from file
    // TODO: replace with some mock-type stuff
    auto figuresDimentions = InputDataReader().fromFile("maleplyty.txt");
    FigureDimentionsGlobalStorage::instance(figuresDimentions);

    // Test genome creation
    CompositeGenome genome(figuresDimentions.size(), objectiveFunction);
    std::cout << "Genome after creation: \n" << genome << std::endl << std::endl;

    // Test genome initialization
    genome.initialize();
    std::cout << "Genome after initialization: \n" << genome << std::endl << std::endl;

    // Test genome mutation
    genome.mutate(1.0);
    std::cout << "Genome after mutation: \n" << genome << std::endl << std::endl;

    // Test genome copying
    std::unique_ptr<CompositeGenome> genomeCopyA (new CompositeGenome(genome));
    std::unique_ptr<CompositeGenome> genomeCopyB (new CompositeGenome(genome));
    genomeCopyA->mutate(1.0);
    std::cout << "Genome after mutation: \n" << genome << std::endl << std::endl;
    std::cout << "Genome copy after mutation: \n" << *genomeCopyA << std::endl << std::endl;

    // Test genome crossover
    std::unique_ptr<CompositeGenome> genomeCopyC (new CompositeGenome(genome));
    std::unique_ptr<CompositeGenome> genomeCopyD (new CompositeGenome(genome));
    genomeCopyA->initialize();
    genomeCopyB->initialize();
    CompositeGenome::DefaultCrossover(*genomeCopyA, *genomeCopyB, genomeCopyC.get(), genomeCopyD.get());
    std::cout << "Parent after crossover: \n" << *genomeCopyA << std::endl << std::endl;
    std::cout << "Parent after crossover: \n" << *genomeCopyB << std::endl << std::endl;
    std::cout << "Child after crossover: \n" << *genomeCopyC << std::endl << std::endl;
    std::cout << "Child after crossover: \n" << *genomeCopyD << std::endl << std::endl;

    // Test genome comparator
    std::cout << "Comparator test: " << genomeCopyA->compare(*genomeCopyB) << std::endl << std::endl;

}