#ifndef IIOTMONITOR_H_INCLUDED
#define IIOTMONITOR_H_INCLUDED
#include <iostream>

using namespace std;

enum ErroCode
{
    ERROR_RANGE = -1,
    SUCCESS
};

// IIoTSensor struct
struct IIoTSensor
{
    double dblTemperature;
    int intHumidity;
    double dblPressure;
    double dblLightIntensity;
    bool blnActive;
};

//Forward declaration
class IIoTSimpleScanner;
class IIoTAdvancedScanner;

// Class
class IIoTMonitor{
public:
    IIoTMonitor();
    IIoTMonitor(int, int, IIoTSensor, bool);
    IIoTMonitor(const IIoTMonitor&);
    ~IIoTMonitor();
    
    string toString() const;
    void scan();
    int getRows() const;
    int getCols() const;
    IIoTSensor getSensor(int intRow, int intCol) const;
    void setSensor(int intRow, int intCol, IIoTSensor recSensor);
    
    // Class constants.
    static const int DEFAULT_HUMIDITY = 20;
    static const int DEFAULT_ROWS = 50;
    static const int DEFAULT_COLS = 50;
    static constexpr double DEFAULT_PRESSURE = 20.0;
    static constexpr double DEFAULT_LIGHT_INTENSITY = 5.0;
    static constexpr double DEFAULT_TEMPERATURE = 10.0;
    static const bool DEFUAULT_CLASS = true;
    
private:
    IIoTSensor** _sensors;
    IIoTSimpleScanner* _SimpleScanner;
    IIoTAdvancedScanner* _AdvancedScanner;
    int _rows;
    int _cols;
    bool _boolScanner;
    
    // Helper (ancillary) functions.
    void alloc(int, int, IIoTSensor, bool);
    void clone(const IIoTMonitor& objOriginal);
    void dealloc();
    void setSensorData();
    void enforceRange(int intValue, int intMin, int intMax) const;
    int rangedRandom(int, int) const;
    
};

#endif // IIOTMONITOR_H_INCLUDED


