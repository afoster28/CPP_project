// PathDependent.h

#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H

#include <vector>
#include "Arrays.h"

// this is an auxiliary class
class CashFlow
{
public:

    double Amount;
    unsigned long TimeIndex;

    // constructor, 0UL stands for 'zero unsigned long'
    CashFlow(unsigned long TimeIndex_=0UL, double Amount_=0.0)
                : TimeIndex(TimeIndex_), Amount(Amount_){};


};

class PathDependent
{
public:

    // constructor takes one array
    PathDependent(const MJArray& lookAtTimes_);

    const MJArray& getLookAtTimes() const;

    // four abstracts methods
    virtual unsigned long maxNumberOfCashFlows() const=0;
    virtual MJArray possibleCashFlowTimes() const=0;
    virtual unsigned long cashFlows(const MJArray& spotValues,
                                    std::vector<CashFlow>& generatedFlows)
                                    const=0;
    virtual PathDependent* clone() const=0;

    virtual ~PathDependent(){}

private:

    MJArray lookAtTimes;

};

#endif
