// PayOffBridge.cpp

#include "PayOffBridge.h"

PayOffBridge::PayOffBridge(const PayOffBridge& original) {
    thePayOffPtr = original.thePayOffPtr -> clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff) {
    thePayOffPtr = innerPayOff.clone();
}


PayOffBridge::~PayOffBridge() {
    delete thePayOffPtr;
}

PayOffBridge& PayOffBridge::operator=(const PayOffBridge& original) {
    if (this != &original) {
        delete thePayOffPtr;
        thePayOffPtr = original.thePayOffPtr->clone();
    }

    return *this;
}

