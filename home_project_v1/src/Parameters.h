// Parameters.h

#ifndef PARAMETERS_H
#define PARAMETERS_H

//This is a base class.
//All its methods are abstract, so this is why we refer to it as an abstract class.
class ParametersInner {
public:
    ParametersInner(){}
    virtual ParametersInner* clone() const=0;
    virtual double getIntegral(double time1, double time2) const=0;
    virtual double getIntegralSquare(double time1, double time2) const=0;

private:

};


//This is a BRIDGING CLASS!
//This class handles the interaction without the outside world,
//and the memory handling. Its only data member is a pointer to an abstract class (ParametersInner).
class Parameters {

public:
    Parameters(const ParametersInner& innerObject);
    Parameters(const Parameters& original);
    Parameters& operator=(const Parameters& original);
    virtual ~Parameters();

    inline double getIntegral(double time1, double time2) const;
    inline double getIntegralSquare(double time1, double time2) const;

    double getMean(double time1, double time2) const;
    double getRootMeanSquare(double time1, double time2) const;

private:
    ParametersInner* InnerObjectPtr;

};


inline double Parameters::getIntegral(double time1, double time2) const {
    return InnerObjectPtr -> getIntegral(time1,time2);
}


inline double Parameters::getIntegralSquare(double time1, double time2) const {
    return InnerObjectPtr -> getIntegralSquare(time1,time2);
}


// This is a subclass of the ParametersInner base class.
// Tt is designed for handling option parameters, that are constant in time.
class ParametersConstant : public ParametersInner {

public:
    ParametersConstant(double constant);

    virtual ParametersInner* clone() const;
    virtual double getIntegral(double time1, double time2) const;
    virtual double getIntegralSquare(double time1, double time2) const;


private:
    double constant;
    double constantSquare;

};

#endif
