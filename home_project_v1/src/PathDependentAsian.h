// PathDependentAsian.h

#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H

#include "PathDependent.h"
#include "PayOffBridge.h"

// this class inherits after PathDependent class
class PathDependentAsian : public PathDependent
{
public:

    //constructor takes three arguments
    PathDependentAsian(const MJArray& lookAtTimes_,
                       double deliveryTime_,
                       const PayOffBridge& thePayOff_);

    virtual unsigned long maxNumberOfCashFlows() const;
    virtual MJArray possibleCashFlowTimes() const;
    virtual unsigned long cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows) const;
    virtual ~PathDependentAsian(){}
    virtual PathDependent* clone() const;

private:

    double deliveryTime;
    PayOffBridge thePayOff;
    unsigned long numberOfTimes;
};


#endif

