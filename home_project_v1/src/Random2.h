// Random2.h

#ifndef RANDOM2_H
#define RANDOM2_H

#include "Arrays.h"

class RandomBase
{
public:

    RandomBase(unsigned long Dimensionality);

    inline unsigned long getDimensionality() const;

    virtual RandomBase* clone() const=0;
    virtual void getUniforms(MJArray& variates)=0;
    virtual void skip(unsigned long numberOfPaths)=0;
    virtual void setSeed(unsigned long seed) =0;
    virtual void reset()=0;

    virtual void getGaussians(MJArray& variates);
    virtual void resetDimensionality(unsigned long newDimensionality);

private:
    unsigned long Dimensionality;

};

unsigned long RandomBase::getDimensionality() const
{
    return Dimensionality;
}

#endif


/*********************************************
 Code based on
 Mark S. Joshi
 "C++ Design Patterns and Derivatives Pricing"
 Cambridge University Press, 2008
 see the copyright disclaimer in the book
 ********************************************/

