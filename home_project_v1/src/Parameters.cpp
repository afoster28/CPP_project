// Parameters.cpp

#include "Parameters.h"

Parameters::Parameters(const ParametersInner& innerObject) {
   InnerObjectPtr = innerObject.clone();
}

Parameters::Parameters(const Parameters& original) {
   InnerObjectPtr = original.InnerObjectPtr->clone();
}

Parameters& Parameters::operator=(const Parameters& original) {
   if (this != &original) {
      delete InnerObjectPtr;
      InnerObjectPtr = original.InnerObjectPtr->clone();
   }
   return *this;
}

Parameters::~Parameters() {
   delete InnerObjectPtr;
}


double Parameters::getMean(double time1, double time2) const {
    double total = getIntegral(time1, time2);
    return total / (time2 - time1);
}

double Parameters::getRootMeanSquare(double time1, double time2) const {
    double total = getIntegralSquare(time1, time2);
    return total / (time2 - time1);
}



ParametersConstant::ParametersConstant(double constant_) {
    constant = constant_;
    constantSquare = constant * constant;
}

ParametersInner* ParametersConstant::clone() const {
    return new ParametersConstant(*this);
}


double ParametersConstant::getIntegral(double time1, double time2) const {
    return (time2 - time1) * constant;
}

double ParametersConstant::getIntegralSquare(double time1, double time2) const {
    return (time2 - time1) * constantSquare;
}

