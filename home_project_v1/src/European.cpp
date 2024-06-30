// European.cpp

#include "European.h"

European::European(const MJArray& lookAtTimes_,
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
unsigned long European::maxNumberOfCashFlows() const
{
     return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray European::possibleCashFlowTimes() const
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
unsigned long European::cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const
{
    double last = spotValues[spotValues.size()-1];  // double last = spotValues[numberOfTimes-1];

    generatedFlows[0].TimeIndex = 0UL;
    generatedFlows[0].Amount = thePayOff(last);

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent* European::clone() const
{
    return new European(*this);
}


// trick: do transition to log
// and go back to the original scale