// Random2.cpp

#include <cstdlib>
#include "Random2.h"
#include "Normals.h"

using namespace std;

void RandomBase::getGaussians(MJArray& variates)
{
    getUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
        double x=variates[i];
        variates[i] = InverseCumulativeNormal(x);
    }
}

void RandomBase::resetDimensionality(unsigned long newDimensionality)
{
    Dimensionality = newDimensionality;
}

RandomBase::RandomBase(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}


/*********************************************
 Code based on
 Mark S. Joshi
 "C++ Design Patterns and Derivatives Pricing"
 Cambridge University Press, 2008
 see the copyright disclaimer in the book
 ********************************************/
