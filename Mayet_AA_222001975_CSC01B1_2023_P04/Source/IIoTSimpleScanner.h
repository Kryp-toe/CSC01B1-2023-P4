#ifndef IIOTSIMPLESCANNER_H
#define IIOTSIMPLESCANNER_H

#include "IIoTScanner.h"
#include <iostream>

using namespace std;

class IIoTSimpleScanner : public IIoTScanner
{
public:
    IIoTSimpleScanner();
    ~IIoTSimpleScanner();
    virtual void scan(IIoTMonitor& objMonitor);
};

#endif





