#include "IIoTSimpleScanner.h"
#include <iostream>

using namespace std;

IIoTSimpleScanner::IIoTSimpleScanner()
{
    setScanLevel(LOW);
}

IIoTSimpleScanner::~IIoTSimpleScanner()  {}

void IIoTSimpleScanner::scan(IIoTMonitor& objMonitor)
{
    for(int r = 0; r < objMonitor.getRows(); r++)
    {
        for(int c = 0; c < objMonitor.getCols(); c++)
        {
            if(objMonitor.getSensor(r, c).dblLightIntensity == 0 ||
                objMonitor.getSensor(r, c).dblPressure == 0 ||
                objMonitor.getSensor(r, c).dblTemperature == 0 ||
                objMonitor.getSensor(r, c).intHumidity == 0)
            {
                
                IIoTSensor recTemp = objMonitor.getSensor(r, c);
                recTemp.blnActive = false;
                objMonitor.setSensor(r, c, recTemp);
                
            }
        }
    }
}