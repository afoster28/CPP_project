// PathDependentAsian.cpp

#include "PathDependentAsian.h"

PathDependentAsian::PathDependentAsian(const MJArray& lookAtTimes_,
                                       double deliveryTime_,
                                       const PayOffBridge& thePayOff_)
                                       :
                                       PathDependent(lookAtTimes_),
                                       deliveryTime(deliveryTime_),
                                       thePayOff(thePayOff_),
                                       numberOfTimes(lookAtTimes_.size())
{
}

// definitions of methods
unsigned long PathDependentAsian::maxNumberOfCashFlows() const
{
     return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray PathDependentAsian::possibleCashFlowTimes() const
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
unsigned long PathDependentAsian::cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const
{
    double sum = spotValues.sum();
    double mean = sum/numberOfTimes;

    generatedFlows[0].TimeIndex = 0UL;
    generatedFlows[0].Amount = thePayOff(mean);

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent* PathDependentAsian::clone() const
{
    return new PathDependentAsian(*this);
}
