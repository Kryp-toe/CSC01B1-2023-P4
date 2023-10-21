#ifndef IIOTSCANNER_H_INCLUDED
#define IIOTSCANNER_H_INCLUDED

#include "IIoTMonitor.h"
#include <iostream>

using namespace std;

class IIoTMonitor;

enum ScanLevel
{
    HIGH,
    LOW
};

class IIoTScanner{
public:
    IIoTScanner();
    virtual void scan(IIoTMonitor& objMonitor) = 0;
    void setScanLevel(ScanLevel Level);
    virtual ~IIoTScanner();
    
private:
    ScanLevel _scanLevel;
};

#endif