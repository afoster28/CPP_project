// ExoticEngine.cpp

#include <cmath>
#include "ExoticEngine.h"

// constructor
ExoticEngine::ExoticEngine(
                 const Wrapper<PathDependent>& theProduct_,
                 const Parameters& r_)
                 :
                 theProduct(theProduct_),
                 r(r_),
                 discounts(theProduct_->possibleCashFlowTimes())
{
    // precomputations all discount factors
    for (unsigned long i=0; i < discounts.size(); i++)
        discounts[i] = exp(-r.getIntegral(0.0, discounts[i]));

    theseCashFlows.resize(theProduct->maxNumberOfCashFlows());
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// a method for LOOPING!
void ExoticEngine::doSimulation(StatisticsMC& theGatherer, unsigned long numberOfPaths)
{
    MJArray spotValues(theProduct->getLookAtTimes().size());

    theseCashFlows.resize(theProduct->maxNumberOfCashFlows());
    double thisValue;

    // this is main Monte Carlo loop
    for (unsigned long i =0; i < numberOfPaths; ++i)
    {
        getOnePath(spotValues); // simulates the path (this method is abstract)
        thisValue = doOnePath(spotValues); //calculate the discounted cash flows
        theGatherer.dumpOneResult(thisValue); //passes the discounted cash flows to the gatherer
    }

    return;
}

// a method for calculating discounted cash flows
double ExoticEngine::doOnePath(const MJArray& spotValues) const
{
    unsigned long NumberFlows = theProduct->cashFlows(spotValues,
                                                      theseCashFlows);
    double Value=0.0;

    // discounting of cashflows (payoff or payoffs for a single path)
    // and summing them together
    for (unsigned i =0; i < NumberFlows; ++i)
        Value += theseCashFlows[i].Amount * discounts[theseCashFlows[i].TimeIndex];

    return Value;
}


