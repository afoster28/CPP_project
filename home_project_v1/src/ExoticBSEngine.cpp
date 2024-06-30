// ExoticBSEngine.cpp

#include <cmath>
#include "ExoticBSEngine.h"

// definition of the abstract class
void ExoticBSEngine::getOnePath(MJArray& spotValues)
{

    theGenerator -> getGaussians(variates);

    double currentLogSpot = logSpot;

    for (unsigned long j=0; j < numberOfTimes; j++)
    {
        currentLogSpot += Drifts[j];
        currentLogSpot += StandardDeviations[j] * variates[j];
        spotValues[j] = exp(currentLogSpot);
    }

    return;
}


// the constructor does relatively a lot of job!
// it precomputes as much as possible (according to Black and Scholes framework)
// before the doSimulation() method is called.
ExoticBSEngine::ExoticBSEngine(const Wrapper<PathDependent>& theProduct_,
                               const Parameters& R_,
                               const Parameters& D_,
                               const Parameters& vol_,
                               const Wrapper<RandomBase>& theGenerator_,
                               double spot_)
                               :
                               ExoticEngine(theProduct_,R_),
                               theGenerator(theGenerator_)
{
    MJArray Times(theProduct_->getLookAtTimes());
    numberOfTimes = Times.size();

    theGenerator->resetDimensionality(numberOfTimes);

    Drifts.resize(numberOfTimes);
    StandardDeviations.resize(numberOfTimes);

    double Variance = vol_.getIntegralSquare(0,Times[0]);

    Drifts[0] = R_.getIntegral(0.0,Times[0]) - D_.getIntegral(0.0,Times[0]) - 0.5 * Variance;
    StandardDeviations[0] = sqrt(Variance);

    for (unsigned long j=1; j < numberOfTimes; ++j)
    {
        double thisVariance = vol_.getIntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_.getIntegral(Times[j-1],Times[j]) - D_.getIntegral(Times[j-1],Times[j])
                    - 0.5 * thisVariance;
        StandardDeviations[j] = sqrt(thisVariance);
    }

    logSpot = log(spot_);
    variates.resize(numberOfTimes);
}

