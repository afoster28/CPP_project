// PathDependentAsianBarrier.cpp

#include "PathDependentAsianBarrier.h"

PathDependentAsianBarrier::PathDependentAsianBarrier(const MJArray& lookAtTimes_,
                                       double deliveryTime_,
                                       const PayOffBridge& thePayOff_,
                                       double barrier_)
                                       :
                                       PathDependent(lookAtTimes_),
                                       deliveryTime(deliveryTime_),
                                       thePayOff(thePayOff_),
                                       barrier(barrier_),
                                       numberOfTimes(lookAtTimes_.size())
{
}

// definitions of methods
unsigned long PathDependentAsianBarrier::maxNumberOfCashFlows() const
{
     return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray PathDependentAsianBarrier::possibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = deliveryTime;
    return tmp;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ! this method is (partially) reponsible for determining payments of the option!!
// is uses the object of the PayOffCall subclass (thePayOff), which previously took
// as argument the final price of underlying. Since we are pricing arithmetic asian call,
// this time it takes mean spot price of underlying.
unsigned long PathDependentAsianBarrier::cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const
{
    double sum = spotValues.sum();
    double mean = sum/numberOfTimes;

    generatedFlows[0].TimeIndex = 0UL;

    double payoff = 0.0;
    if (spotValues.min() > barrier ) payoff = thePayOff(mean);

    generatedFlows[0].Amount = payoff;

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent* PathDependentAsianBarrier::clone() const
{
    return new PathDependentAsianBarrier(*this);
}
