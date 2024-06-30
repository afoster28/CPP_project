// European.h

#ifndef EUROPEAN_H
#define EUROPEAN_H

#include "PathDependent.h"
#include "PayOffBridge.h"

// this class inherits after PathDependent class
class European : public PathDependent
{
public:

    //constructor takes three arguments
    European(const MJArray& lookAtTimes_,
                       double deliveryTime_,
                       const PayOffBridge& thePayOff_);

    virtual unsigned long maxNumberOfCashFlows() const;
    virtual MJArray possibleCashFlowTimes() const;
    virtual unsigned long cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const;
    virtual ~European(){}
    virtual PathDependent* clone() const;

private:

    double deliveryTime;
    PayOffBridge thePayOff;
    unsigned long numberOfTimes;
};


#endif





