// EuropeanBarrier.cpp

#include "EuropeanBarrier.h"

EuropeanBarrier::EuropeanBarrier(const MJArray& lookAtTimes_,
                                       double deliveryTime_,
                                       const PayOffBridge& thePayOff_,
                                       double barrier_)
                                       :
                                       PathDependent(lookAtTimes_), // initialiser list, e.g. PathDependent = lookAtTimes; this way don't need to define in {}
                                       deliveryTime(deliveryTime_),
                                       thePayOff(thePayOff_),
                                       barrier(barrier_),
                                       numberOfTimes(lookAtTimes_.size())
{
}

// definitions of methods
unsigned long EuropeanBarrier::maxNumberOfCashFlows() const
{
     return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray EuropeanBarrier::possibleCashFlowTimes() const
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
unsigned long EuropeanBarrier::cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const
{
    double last = spotValues[spotValues.size()-1];  // double last = spotValues[numberOfTimes-1];
    // instead of last price would calc arithmetic average for asian option

    generatedFlows[0].TimeIndex = 0UL;

    double payoff = 0.0;
    if (spotValues.min() > barrier ) payoff = thePayOff(last);

    generatedFlows[0].Amount = payoff; // otherwise thePayoff(last) for European option

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent* EuropeanBarrier::clone() const
{
    return new EuropeanBarrier(*this);
}


// trick: do transition to log
// and go back to the original scale