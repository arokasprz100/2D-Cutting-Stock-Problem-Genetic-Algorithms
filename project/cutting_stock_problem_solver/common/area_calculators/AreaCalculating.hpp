#pragma once

class AreaCalculating
{
public:

    virtual int calculate(const CompositeGenome& genome, const Pieces& pieces) const = 0;
};