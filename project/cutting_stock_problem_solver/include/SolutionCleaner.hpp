#pragma once

#include "Pieces.hpp"

class CompositeGenome;

class SolutionCleaner
{
public:

    static void moveAllFiguresTowardsTheOrigin(CompositeGenome& compositeGenome);

    static void tryToAddRemainingFigures(CompositeGenome& compositeGenome, const Pieces& pieces);
};