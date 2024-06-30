// PathDependentAsianBarrier.h

#ifndef PATH_DEPENDENT_ASIAN_BARRIER_H
#define PATH_DEPENDENT_ASIAN_BARRIER_H

#include "PathDependent.h"
#include "PayOffBridge.h"

// this class inherits after PathDependent class
class PathDependentAsianBarrier : public PathDependent
{
public:

    //constructor takes three arguments
    PathDependentAsianBarrier(const MJArray& lookAtTimes_,
                       double deliveryTime_,
                       const PayOffBridge& thePayOff_,
                       double barrier_);

    virtual unsigned long maxNumberOfCashFlows() const;
    virtual MJArray possibleCashFlowTimes() const;
    virtual unsigned long cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const;
    virtual ~PathDependentAsianBarrier(){}
    virtual PathDependent* clone() const;

private:
    double barrier;
    double deliveryTime;
    PayOffBridge thePayOff;
    unsigned long numberOfTimes;
};


#endif

