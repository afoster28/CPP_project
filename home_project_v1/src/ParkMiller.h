// ParkMiller.h

#ifndef PARK_MILLER_H
#define PARK_MILLER_H

#include "Random2.h"

class ParkMiller {
public:
    ParkMiller(long seed = 1);
    long getOneRandomInteger();
    void setSeed(long seed);
    static unsigned long getMax();
    static unsigned long getMin();

private:
    long seed;
};

class RandomParkMiller : public RandomBase {
public:
    RandomParkMiller(unsigned long dimensionality, unsigned long seed = 1);
    virtual RandomBase* clone() const;
    virtual void getUniforms(MJArray& variates);
    virtual void skip(unsigned long numberOfPaths);
    virtual void setSeed(unsigned long seed);
    virtual void reset();
    virtual void resetDimensionality(unsigned long newDimensionality);

private:
    ParkMiller innerGenerator;
    unsigned long initialSeed;
    double reciprocal;
};
#endif



