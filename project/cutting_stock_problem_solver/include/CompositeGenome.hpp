#pragma once

#include <ga/ga.h>
#include <ga/GA1DArrayGenome.h>
#include <ga/GAAllele.h>

#include <algorithm>

#include "RandomNumberGenerator.hpp"
#include "FigureDimentionsGlobalStorage.hpp"
#include "SolutionCleaner.hpp"
#include "Sheet.hpp"

class CompositeGenome : public GAGenome
{
public:

    GADefineIdentity("CompositeGenome", 201);

    // STATIC METHODS //////////////////////////
    static void CompositeInitializer(GAGenome& genome);
    static int CompositeMutator(GAGenome& genome, float mutationProbability);
    static float CompositeComparator(const GAGenome& genomeA, const GAGenome& genomeB);
    static int CompositeCrossover(const GAGenome& parentA, const GAGenome& parentB, GAGenome* childA, GAGenome* childB);

    static constexpr auto DefaultCrossover = CompositeCrossover;

    // NON-STATIC METHODS /////////////////////
    CompositeGenome(int numberOfFigures, GAGenome::Evaluator ev = NULL);
    CompositeGenome(const CompositeGenome& compositeGenome);
    virtual ~CompositeGenome();

    GAGenome* clone(GAGenome::CloneMethod) const;
    void copy(const GAGenome& genome);
    CompositeGenome& operator=(const GAGenome& genome);

    std::tuple<int, int, int, int> getByIndex(int index) const;


    // INPUT / OUTPUT STREAM METHODS ///////////////////
    int write(std::ostream& os) const;
    void printSingleArrayGenome(GA1DArrayAlleleGenome<int>* toPrint, std::ostream& os) const;

    friend SolutionCleaner;

private:
    GA1DArrayAlleleGenome<int>* xPositions;
    GA1DArrayAlleleGenome<int>* yPositions;
    GA1DArrayAlleleGenome<int>* isUsed;
    GA1DArrayAlleleGenome<int>* isRotated;
};
