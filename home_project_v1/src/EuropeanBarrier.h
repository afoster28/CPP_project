// EuropeanBarrier.h

#ifndef EUROPEANBARRIER_H
#define EUROPEANBARRIER_H

#include "PathDependent.h"
#include "PayOffBridge.h"

// this class inherits after PathDependent class
class EuropeanBarrier : public PathDependent
{
public:

    //constructor takes three arguments
    EuropeanBarrier(const MJArray& lookAtTimes_,
                       double deliveryTime_,
                       const PayOffBridge& thePayOff_,
                       double barrier_); // argument

    virtual unsigned long maxNumberOfCashFlows() const;
    virtual MJArray possibleCashFlowTimes() const;
    virtual unsigned long cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const;
    virtual ~EuropeanBarrier(){}
    virtual PathDependent* clone() const;

private:
    double barrier; // data member
    double deliveryTime;
    PayOffBridge thePayOff;
    unsigned long numberOfTimes;
};


#endif





