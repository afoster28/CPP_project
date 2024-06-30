// ExoticBSEngine.h

#ifndef EXOTIC_BS_ENGINE_H
#define EXOTIC_BS_ENGINE_H

#include "ExoticEngine.h"
#include "Random2.h"

class ExoticBSEngine : public ExoticEngine
{
public:

      ExoticBSEngine(const Wrapper<PathDependent>& theProduct_,
                     const Parameters& R_,
                     const Parameters& D_,
                     const Parameters& vol_,
                     const Wrapper<RandomBase>& theGenerator_,
                     double spot_);

      virtual void getOnePath(MJArray& spotValues);
      virtual ~ExoticBSEngine(){}


private:

    Wrapper<RandomBase> theGenerator;
    MJArray Drifts;
    MJArray StandardDeviations;
    double logSpot;
    unsigned long numberOfTimes;
    MJArray variates;
};

#endif

