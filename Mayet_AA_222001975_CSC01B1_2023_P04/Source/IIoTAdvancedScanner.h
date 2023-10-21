#ifndef IIOTADVANCEDSCANNER_H
#define IIOTADVANCEDSCANNER_H

#include "IIoTScanner.h"
#include <iostream>

using namespace std;

class IIoTAdvancedScanner : public IIoTScanner
{
public:
    IIoTAdvancedScanner();
    ~IIoTAdvancedScanner();
    virtual void scan(IIoTMonitor& objMonitor);
};

#endif






