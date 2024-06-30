// PayOffBridge.h

#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include "PayOff3.h"

class PayOffBridge {
public:
    PayOffBridge(const PayOffBridge& original);
    PayOffBridge(const PayOff& innerPayOff);

    inline double operator()(double spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);

private:
    PayOff* thePayOffPtr;

};

inline double PayOffBridge::operator()(double spot) const {
    return thePayOffPtr->operator ()(spot);
}

#endif
