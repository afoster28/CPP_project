// MCStatistics.h

#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class StatisticsMC{
public:

    StatisticsMC(){}

    virtual void dumpOneResult(double result)=0;
    virtual std::vector<std::vector<double> > getResultsSoFar() const=0;
    virtual StatisticsMC* clone() const=0;
    virtual ~StatisticsMC(){}

private:

};


class StatisticsMean : public StatisticsMC{

public:

    StatisticsMean();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double> > getResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
    unsigned long PathsDone;

};

#endif
