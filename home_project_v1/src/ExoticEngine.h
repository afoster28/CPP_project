// ExoticEngine.h

#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include <vector>
#include "wrapper.h"
#include "Parameters.h"
#include "PathDependent.h"
#include "MCStatistics.h"

class ExoticEngine
{
public:

    ExoticEngine(const Wrapper<PathDependent>& theProduct_,
                 const Parameters& r_);

    // abstract method!
    virtual void getOnePath(MJArray& spotValues)=0;

    void doSimulation(StatisticsMC& theGatherer, unsigned long numberOfPaths);
    virtual ~ExoticEngine(){}
    double doOnePath(const MJArray& spotValues) const;

private:

    Wrapper<PathDependent> theProduct;
    Parameters r;
    MJArray discounts;
    mutable std::vector<CashFlow> theseCashFlows;
};

#endif

