// PortfolioPricer.cpp

#include <Rcpp.h>
#include "ParkMiller.h"
#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include "AntiThetic.h"
#include "PathDependentAsian.h"
#include "ExoticBSEngine.h"
#include "European.h"
#include "EuropeanBarrier.h"
#include "PathDependentAsianBarrier.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
double MCAsianBarrierPortfolioPricer(
    double expiry = 5.0 / 12.0,
    double spot = 115,
    double vol = 0.25,
    double r = 0.05,
    double d = 0.0,
    unsigned long int numberOfPaths = 1000000,
    unsigned long int numberOfDates = 126,
    double barrier = 0.8 * 115
)
{
    double strike;
    double position;

    // Define long call butterfly portfolio of strike-position pairs
    vector<vector<double>> options;
    options.push_back({110, 1}); // long ITM call
    options.push_back({115, -1}); // short ATM call
    options.push_back({115, -1}); // short ATM call
    options.push_back({120, 1}); // long OTM call
    double portfolioPrice = 0.0;

    for (int option = 0; option < options.size(); option++)
    {
        strike = options[option][0];
        position = options[option][1]; // 1 for long, -1 for short

        // Create an object of PayOffCall type.
        PayOffCall thePayOff(strike);

        // Create an array (an object of type MJArray) which will store
        // time index for each date (interval).
        MJArray times(numberOfDates);
        for (unsigned long i = 0; i < numberOfDates; i++)
        {
            times[i] = (i + 1.0) * expiry / numberOfDates;
        }
        // Note, that for daily intervals expiry/numberOfDates should equal to 1/252.

        // Create constant volatility, risk-free rate and dividend rate parameters
        // (these are objects of already well known ParametersConstant class).
        ParametersConstant volParam(vol);
        ParametersConstant rParam(r);
        ParametersConstant dParam(d);

        // Create the product, ie. an object of the PathDependentAsian class.
        // This class inherits after the PathDependent base class.
        // Note, that one of the arguments of the constructor is thePayOff,
        // ie. the object of the PayOffCall class.
        // PathDependentAsian theOption(times, expiry, thePayOff);
        // European theOption(times, expiry, thePayOff);
        // EuropeanBarrier theOption(times, expiry, thePayOff, barrier);
        PathDependentAsianBarrier theOption(times, expiry, thePayOff, barrier);

        // Create the object of the StatisticsMean class
        // responsible for calculating the mean discounted pay-off.
        // Note, that the StatisticsMean class inherits after StatisticsMC base class.
        StatisticsMean gatherer;

        // Create an object of the ConvergenceTable.
        // We use here the decoration pattern: gatherer2 can take the gatherer as argument
        // and store it as its data member. This trick is called 'the decoration pattern'.
        // Note, that the ConvergenceTable class also inherits after StatisticsMC base class.
        ConvergenceTable gatherer2(gatherer);

        // Create an object of the RandomParkMiller class, responsible for drawing normal variates.
        // RandomParkMiller inherits after RandomBase base class.
        // numberOfDates serves as dimensionality, for example: for expiry = 0.5 we have 126 days to maturity,
        // and this means, that for each of 126 we have to simulate increment, ie. draw a single gaussian variate.
        // The second argument (seed) is missing here, as it has a default value.
        RandomParkMiller generator(numberOfDates);

        // Create an object of the AntiThetic class.
        // AntiThetic class also inherits after the RandomBase class.
        // generator2 can take generator as its argument and store it as its data member.
        // AntiThetic generator2(generator);

        // Create our ENGINE: an object of the ExoticBSEngine. This class inherits after the ExoticEngine base class
        // and is responsible for simulating the single paths of underlying prices, according to the
        // Black-Scholes assumptions, ie. under geometric Brownian motion
        // Having created theEngine, we put into it:
        // 1) the product, ie. the specific (path-dependent) option, with defined payoff function
        // 2) three (constant) stochastic process parameters
        // 3) pseudo-random numbers generator, decorated with the Antithetic subclass
        // 4) spot price of the underlying (at the moment of pricing)
        // ExoticBSEngine theEngine(theOption, rParam, dParam, volParam, generator2, spot); // with antithetic
        ExoticBSEngine theEngine(theOption, rParam, dParam, volParam, generator, spot); // without antithetic

        // Run OUR ENGINE: call the doSimulation() method of theEngine (i.e the object of the ExoticBSEngine subclass)
        // This method does the job of the SimpleMonteCarlo() method, ie. performs looping.
        // It needs to know: which statistics gatherer to use and how many times to loop.
        theEngine.doSimulation(gatherer2, numberOfPaths);

        // We gather the results, ie. the convergence table after the desired number of loops
        // into results of type 'vector of vector of doubles'.
        vector<vector<double>> results = gatherer2.getResultsSoFar();

        // Add Asian barrier call price to portfolio price
        portfolioPrice += results[results.size() - 1][0] * position;
    }

    return portfolioPrice;
}
