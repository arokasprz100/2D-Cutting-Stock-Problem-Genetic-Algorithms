#include "CompositeGenome.hpp"
#include "RandomNumberGenerator.hpp"

template<>
int GAAlleleSet<int>::allele() const {
    return randomInteger(lower(), upper());
}