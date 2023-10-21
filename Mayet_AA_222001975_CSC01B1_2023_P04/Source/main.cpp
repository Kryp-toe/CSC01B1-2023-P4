#include "IIoTMonitor.h"
#include <ctime>

//using namespace IOTSpace;

int main()
{
    srand(time(nullptr));
    
    IIoTSensor recSensor;
    
    recSensor.dblTemperature = 0;
    recSensor.dblLightIntensity = 0;
    recSensor.dblPressure = 0;
    recSensor.intHumidity = 0;
    
    IIoTMonitor objMonitor(25, 25, recSensor, false);
    
    objMonitor.scan();
    
    cout << objMonitor.toString();
    
    return SUCCESS;
}




