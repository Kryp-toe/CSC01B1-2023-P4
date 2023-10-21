#include "IIoTScanner.h"
#include <iostream>

using namespace std;

IIoTScanner::IIoTScanner() {}

void IIoTScanner::scan(IIoTMonitor& objMonitor)
{
    
}

void IIoTScanner::setScanLevel(ScanLevel Level)
{
    _scanLevel = Level;
}

IIoTScanner::~IIoTScanner() {}