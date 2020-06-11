#pragma once

#include "AlgorithmSettings.hpp"
#include <ga/ga.h>
#include <ga/GA1DArrayGenome.h>
#include <ga/GAAllele.h>

#include <algorithm>
#include <tuple>
#include "RandomNumberGenerator.hpp"
#include "Pieces.hpp"
#include "SolutionCleaner.hpp"

// TODO: refactor - replace new and delete with unique_ptrs, move redundant code to functions
class CompositeGenome : public GAGenome
{
public:

    GADefineIdentity("CompositeGenome", 201);

    // STATIC METHODS //////////////////////////

    static void CompositeInitializer(GAGenome& genome) {
        CompositeGenome& compositeGenome = dynamic_cast<CompositeGenome&>(genome);
        int numberOfFigures = compositeGenome.xPositions->length();
        int figureOnTheTopLeft = randomInteger(0, numberOfFigures - 1);
        int isRotated = randomInteger(0, 1);

        compositeGenome.xPositions->initialize();
        compositeGenome.yPositions->initialize();
        compositeGenome.isRotated->initialize();
        for (int i = 0; i < numberOfFigures; ++i) {
            compositeGenome.isUsed->gene(i, 0);
        }

        compositeGenome.isUsed->gene(figureOnTheTopLeft, 1);
        compositeGenome.isRotated->gene(figureOnTheTopLeft, isRotated);
        compositeGenome.xPositions->gene(figureOnTheTopLeft, 0);
        compositeGenome.yPositions->gene(figureOnTheTopLeft, 0);

        compositeGenome._evaluated = gaFalse;
    }



    static int CompositeMutator(GAGenome& genome, float mutationProbability) {
        CompositeGenome& compositeGenome = dynamic_cast<CompositeGenome&>(genome);

        int numberOfMutations = 0;
        for (int i = 0; i < compositeGenome.xPositions->length(); ++i) {

            if (randomUniformRealNumber() < mutationProbability) {
                ++numberOfMutations;

                int newXPosition = (compositeGenome.xPositions->gene(i) + static_cast<int>(randomNormalRealNumber()));
                int newYPosition = (compositeGenome.yPositions->gene(i) + static_cast<int>(randomNormalRealNumber()));

                newXPosition = newXPosition < 0 ? 0 : newXPosition;
                newYPosition = newYPosition < 0 ? 0 : newYPosition;

                if (randomUniformRealNumber() < 0.5) {
                    compositeGenome.isUsed->gene(i, !compositeGenome.isUsed->gene(i));
                }

                if (randomUniformRealNumber() < 0.5) {
                    compositeGenome.isRotated->gene(i, !compositeGenome.isRotated->gene(i));
                }

            }   

        }

        if (randomUniformRealNumber() < 0.25) {
            SolutionCleaner::moveAllFiguresTowardsTheOrigin(compositeGenome);
        }

        compositeGenome._evaluated = gaFalse;
        return numberOfMutations + 1;
    }



    static float CompositeComparator(const GAGenome& genomeA, const GAGenome& genomeB) {
        const CompositeGenome& sisterGenome = static_cast<const CompositeGenome&>(genomeA);
        const CompositeGenome& brotherGenome = static_cast<const CompositeGenome&>(genomeB);
        return 0.25 * (sisterGenome.xPositions->compare(*brotherGenome.xPositions) 
            + sisterGenome.yPositions->compare(*brotherGenome.yPositions)
            + sisterGenome.isUsed->compare(*brotherGenome.isUsed)
            + sisterGenome.isRotated->compare(*brotherGenome.isRotated));
    }


    static int CompositeCrossover(const GAGenome& parentA, const GAGenome& parentB, GAGenome* childA, GAGenome* childB) {
        const CompositeGenome& parentAComposite = static_cast<const CompositeGenome&>(parentA);
        const CompositeGenome& parentBComposite = static_cast<const CompositeGenome&>(parentB);

        int counter = 0;

        GAGenome::SexualCrossover xCross = parentAComposite.xPositions->sexual();
        GAGenome::SexualCrossover yCross = parentAComposite.yPositions->sexual();
        GAGenome::SexualCrossover usedCross = parentAComposite.isUsed->sexual();
        GAGenome::SexualCrossover rotatedCross = parentAComposite.isRotated->sexual();

        if (childA && childB) {
            CompositeGenome& childAComposite = static_cast<CompositeGenome&>(*childA);
            CompositeGenome& childBComposite = static_cast<CompositeGenome&>(*childB);

            (*xCross)( *(parentAComposite.xPositions), *(parentBComposite.xPositions), 
                childAComposite.xPositions, childBComposite.xPositions);
            (*yCross)( *(parentAComposite.yPositions), *(parentBComposite.yPositions), 
                childAComposite.yPositions, childBComposite.yPositions);
            (*usedCross)( *(parentAComposite.isUsed), *(parentBComposite.isUsed), 
                childAComposite.isUsed, childBComposite.isUsed);
            (*rotatedCross)( *(parentAComposite.isRotated), *(parentBComposite.isRotated), 
                childAComposite.isRotated, childBComposite.isRotated);

            childAComposite._evaluated = gaFalse;
            childBComposite._evaluated = gaFalse;
            counter = 2;
        }
        else if (childA) {
            CompositeGenome& childAComposite = static_cast<CompositeGenome&>(*childA);

            (*xCross)( *(parentAComposite.xPositions), *(parentBComposite.xPositions), 
                childAComposite.xPositions, 0);
            (*yCross)( *(parentAComposite.yPositions), *(parentBComposite.yPositions), 
                childAComposite.yPositions, 0);
            (*usedCross)( *(parentAComposite.isUsed), *(parentBComposite.isUsed), 
                childAComposite.isUsed, 0);
            (*rotatedCross)( *(parentAComposite.isRotated), *(parentBComposite.isRotated), 
                childAComposite.isRotated, 0);

            childAComposite._evaluated = gaFalse;
            counter = 1;
        }
        else if (childB) {
            CompositeGenome& childBComposite = static_cast<CompositeGenome&>(*childB);

            (*xCross)( *(parentAComposite.xPositions), *(parentBComposite.xPositions), 
                0, childBComposite.xPositions);
            (*yCross)( *(parentAComposite.yPositions), *(parentBComposite.yPositions), 
                0, childBComposite.yPositions);
            (*usedCross)( *(parentAComposite.isUsed), *(parentBComposite.isUsed), 
                0, childBComposite.isUsed);
            (*rotatedCross)( *(parentAComposite.isRotated), *(parentBComposite.isRotated), 
                0, childBComposite.isRotated);

            childBComposite._evaluated = gaFalse;
            counter = 1;
        }

        return counter;
    }


    static constexpr auto DefaultCrossover = CompositeCrossover;

    // NON-STATIC METHODS /////////////////////

    CompositeGenome(int numberOfPieces, GAGenome::Evaluator ev = NULL) : GAGenome(CompositeInitializer, CompositeMutator, CompositeComparator) {
        evaluator(ev);
        crossover(CompositeCrossover);

        GAAlleleSet<int> xPositionsAlleleSet(0, AlgorithmSettings::xPositionUpperBound, GAAllele::INCLUSIVE, GAAllele::EXCLUSIVE);
        xPositions = new GA1DArrayAlleleGenome<int>(numberOfPieces, xPositionsAlleleSet, ev);

        GAAlleleSet<int> yPositionsAlleleSet(0, AlgorithmSettings::yPositionUpperBound, GAAllele::INCLUSIVE, GAAllele::EXCLUSIVE);
        yPositions = new GA1DArrayAlleleGenome<int>(numberOfPieces, yPositionsAlleleSet);

        GAAlleleSet<int> isUsedAlleleSet(0, 1, GAAllele::INCLUSIVE, GAAllele::INCLUSIVE);
        isUsed = new GA1DArrayAlleleGenome<int>(numberOfPieces, isUsedAlleleSet);

        GAAlleleSet<int> isRotatedAlleleSet(0, 1, GAAllele::INCLUSIVE, GAAllele::INCLUSIVE);
        isRotated = new GA1DArrayAlleleGenome<int>(numberOfPieces, isRotatedAlleleSet);
    }

    CompositeGenome(const CompositeGenome& compositeGenome) {
        xPositions = new GA1DArrayAlleleGenome<int>(*(compositeGenome.xPositions));
        yPositions = new GA1DArrayAlleleGenome<int>(*(compositeGenome.yPositions));
        isUsed = new GA1DArrayAlleleGenome<int>(*(compositeGenome.isUsed));
        isRotated = new GA1DArrayAlleleGenome<int>(*(compositeGenome.isRotated));
        copy(compositeGenome);
    }

    virtual ~CompositeGenome() {
        delete xPositions;
        delete yPositions;
        delete isUsed;
        delete isRotated;
    }


    GAGenome* clone(GAGenome::CloneMethod) const {
        return new CompositeGenome(*this);
    }

    void copy(const GAGenome& genome) {
        if (&genome != this && sameClass(genome)) {
            GAGenome::copy(genome);
            const CompositeGenome& compositeGenome = static_cast<const CompositeGenome&>(genome);
            xPositions->copy(*(compositeGenome.xPositions));
            yPositions->copy(*(compositeGenome.yPositions));
            isUsed->copy(*(compositeGenome.isUsed));
            isRotated->copy(*(compositeGenome.isRotated));
        }
    }

    CompositeGenome& operator=(const GAGenome& genome) {
        copy(genome);
        return *this;
    }

    std::tuple<int, int, int, int> getByIndex(int index) const {
        return std::make_tuple(xPositions->gene(index), yPositions->gene(index), isUsed->gene(index), isRotated->gene(index));
    }


    // INPUT / OUTPUT STREAM METHODS ///////////////////

    int write(std::ostream& os) const {
        os << "X positions: ";
        printSingleArrayGenome(xPositions, os);
        os << "\nY positions: ";
        printSingleArrayGenome(yPositions, os);
        os << "\nAre used: ";
        printSingleArrayGenome(isUsed, os);
        os << "\nAre rotated: ";
        printSingleArrayGenome(isRotated, os);
        os << "\n";
        return os.fail() ? 1 : 0;
    }

    void printSingleArrayGenome(GA1DArrayAlleleGenome<int>* toPrint, std::ostream& os) const {
        for (int i = 0; i < toPrint->length(); ++i) {
            os << (toPrint->gene(i)) << " ";
        }
    }

    friend SolutionCleaner;

private:
    GA1DArrayAlleleGenome<int>* xPositions;
    GA1DArrayAlleleGenome<int>* yPositions;
    GA1DArrayAlleleGenome<int>* isUsed;
    GA1DArrayAlleleGenome<int>* isRotated;

};

