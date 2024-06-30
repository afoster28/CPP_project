// ConvergenceTable.cpp

#include "ConvergenceTable.h"

// constructor
ConvergenceTable::ConvergenceTable(const Wrapper<StatisticsMC>& Inner_)
: Inner(Inner_)
{
    StoppingPoint=2;
    PathsDone=0;
}

// definition of clone() method
StatisticsMC* ConvergenceTable::clone() const
{
    return new ConvergenceTable(*this);
}

// definition of dumpOneResult() method
void ConvergenceTable::dumpOneResult(double result)
{
    Inner->dumpOneResult(result);
    ++PathsDone;

    if (PathsDone == StoppingPoint)
    {
        StoppingPoint*=2;
        std::vector<std::vector<double> > thisResult(Inner->getResultsSoFar());

        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(PathsDone);
            ResultsSoFar.push_back(thisResult[i]);
        }
    }

    return;

}

// definition of getResultsSoFar() method
std::vector<std::vector<double> >  ConvergenceTable::getResultsSoFar() const
{
    std::vector<std::vector<double> > tmp(ResultsSoFar);

    if (PathsDone*2 != StoppingPoint)
    {
        std::vector<std::vector<double> > thisResult(Inner->getResultsSoFar());

        for (unsigned long i=0; i < thisResult.size(); i++)
        {
            thisResult[i].push_back(PathsDone);
            tmp.push_back(thisResult[i]);
        }
    }
    return tmp;
}
