#pragma once

class CompositeGenome; // forward declaration


class SolutionCleaner
{
public:
    static void moveAllFiguresTowardsTheOrigin(CompositeGenome& compositeGenome);
    static void tryToAddRemainingFigures(CompositeGenome& compositeGenome);
    static void removeFiguresThatBreakTheSolution(CompositeGenome& compositeGenome);
};