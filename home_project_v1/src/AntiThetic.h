// AntiThetic.h

#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include "Random2.h"
#include "wrapper.h"

class AntiThetic : public RandomBase {

public:
    AntiThetic(const Wrapper<RandomBase>& innerGenerator );
    virtual RandomBase* clone() const;
    virtual void getUniforms(MJArray& variates);
    virtual void skip(unsigned long numberOfPaths);
    virtual void setSeed(unsigned long seed);
    virtual void resetDimensionality(unsigned long newDimensionality);
    virtual void reset();
private:
    Wrapper<RandomBase> innerGenerator;
    bool oddEven;
    MJArray nextVariates;
};

#endif

