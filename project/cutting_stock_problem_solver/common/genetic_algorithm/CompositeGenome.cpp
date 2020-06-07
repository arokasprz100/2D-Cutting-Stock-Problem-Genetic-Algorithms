#include "CompositeGenome.hpp"
#include "RandomNumberGenerator.hpp"


// TODO: check if everything works
template<>
int GAAlleleSet<int>::allele() const {
    return randomInteger(lower(), upper());
}