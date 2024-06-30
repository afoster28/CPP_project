// PathDependent.cpp

#include "PathDependent.h"

// constructor definition
PathDependent::PathDependent(const MJArray& lookAtTimes_)
                        : lookAtTimes(lookAtTimes_)
{}

// definition of the only one non-abstract method
const MJArray& PathDependent::getLookAtTimes() const
{
    return lookAtTimes;
}
