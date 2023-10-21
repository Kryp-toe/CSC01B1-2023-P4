#include "IIoTMonitor.h"
#include "IIoTSimpleScanner.h"
#include "IIoTAdvancedScanner.h"
#include <sstream>

IIoTMonitor::IIoTMonitor(): IIoTMonitor(DEFAULT_ROWS, DEFAULT_COLS, {DEFAULT_TEMPERATURE, DEFAULT_HUMIDITY, DEFAULT_PRESSURE, DEFAULT_LIGHT_INTENSITY}, DEFUAULT_CLASS){
    
}

IIoTMonitor::IIoTMonitor(int intRows, int intCols, IIoTSensor recSensor, bool boolScanner)
{
    // allocate memory
    alloc(intRows, intCols, recSensor, boolScanner);
    
    // setSensorData
    setSensorData();
}

IIoTMonitor::IIoTMonitor(const IIoTMonitor& objMonitor): IIoTMonitor(objMonitor._rows, objMonitor._cols, {DEFAULT_TEMPERATURE, DEFAULT_HUMIDITY, DEFAULT_PRESSURE, DEFAULT_LIGHT_INTENSITY}, DEFUAULT_CLASS)
{
    // Make a deep copy
    clone(objMonitor);
}

void IIoTMonitor::alloc(int intRows, int intCols, IIoTSensor recSensor, bool boolScanner)
{
    // Set Private Properties
    _rows = intRows;
    _cols = intCols;
    _boolScanner = boolScanner;
    
    // Allocate Memory for 2D Array
    _sensors = new IIoTSensor*[intRows];
    for(int r = 0; r < intRows; r++)
    {
        _sensors[r] = new IIoTSensor[intCols];
        
        for(int c = 0; c < intCols; c++){
            
            _sensors[r][c].dblTemperature = recSensor.dblTemperature;
            _sensors[r][c].intHumidity = recSensor.intHumidity;
            _sensors[r][c].dblPressure = recSensor.dblPressure;
            _sensors[r][c].dblLightIntensity = recSensor.dblLightIntensity;
            _sensors[r][c].blnActive = true;
        }
    }
    
    if(_boolScanner)
    {
        _AdvancedScanner = new IIoTAdvancedScanner();
    }
    else
    {
        _SimpleScanner = new IIoTSimpleScanner();
    }
}

void IIoTMonitor::clone(const IIoTMonitor& objOriginal)
{
    for(int r = 0; r < _rows; r++)
    {
        for(int c = 0; c < _cols; c++)
        {
            _sensors[r][c].dblTemperature = objOriginal._sensors[r][c].dblTemperature;
            _sensors[r][c].intHumidity = objOriginal._sensors[r][c].intHumidity;
            _sensors[r][c].dblPressure = objOriginal._sensors[r][c].dblPressure;
            _sensors[r][c].dblLightIntensity = objOriginal._sensors[r][c].dblLightIntensity;
            _sensors[r][c].blnActive = objOriginal._sensors[r][c].blnActive;
        }
    }
}

IIoTMonitor::~IIoTMonitor()
{
    dealloc();
}

void IIoTMonitor::dealloc()
{
    for(int r = 0; r < _rows; r++)
        delete [] _sensors[r];
        
    delete [] _sensors;
    
    if(_boolScanner)
    {
        delete _AdvancedScanner;
    }
    else
    {
        delete _SimpleScanner;
    }
}

void IIoTMonitor::setSensorData()
{
    for(int r = 0; r < _rows; r++)
    {
        for(int c = 0; c < _cols; c++)
        {
            _sensors[r][c].dblTemperature = (double) rangedRandom(0, 50);
            _sensors[r][c].intHumidity = rangedRandom(0, 40);
            _sensors[r][c].dblPressure = (double) rangedRandom(0, 40);
            _sensors[r][c].dblLightIntensity = (double) rangedRandom(10000, 30000);
        }
    }
}

void IIoTMonitor::scan()
{
    if(_boolScanner)
    {
        _AdvancedScanner->scan(*this);
    }
    else
    {
        _SimpleScanner->scan(*this);
    }
}

string IIoTMonitor::toString() const
{
    stringstream ss;
    for(int r = 0; r < _rows; r++)
    {
        for(int c = 0; c < _cols; c++)
        {
            int numFaultySensors = 0;
            char sensorChar = '.';
            
            if(_sensors[r][c].blnActive)
            {
                if(_sensors[r][c].dblTemperature <= 0 || _sensors[r][c].dblTemperature > 40)
                {
                    numFaultySensors++;
                    sensorChar = 'T';
                }
                
                if(_sensors[r][c].intHumidity <= 0 || _sensors[r][c].intHumidity > 30)
                {
                    numFaultySensors++;
                    sensorChar = 'H';
                }
                
                if(_sensors[r][c].dblPressure <= 0 || _sensors[r][c].dblPressure > 30.2)
                {
                    numFaultySensors++;
                    sensorChar = 'P';
                }
                
                if(_sensors[r][c].dblLightIntensity < 0 || _sensors[r][c].dblLightIntensity > 100000)
                {
                    numFaultySensors++;
                    sensorChar = 'L';
                }
                
                // Assign characters
                if(numFaultySensors > 1)
                {
                    ss << 'M' << ' ';
                }
                else{
                    ss << sensorChar << ' ';
                }
                
            }
            else{
                ss << 'X' << ' ';
            }
        }
        
        ss << endl;
    }
    
    return ss.str();
}

int IIoTMonitor::getRows() const
{
    return _rows;
}

int IIoTMonitor::getCols() const
{
    return _cols;
}

IIoTSensor IIoTMonitor::getSensor(int intRow, int intCol) const
{
    enforceRange(intRow, 0, _rows - 1);
    enforceRange(intCol, 0, _cols - 1);
    return _sensors[intRow][intCol];
}

void IIoTMonitor::setSensor(int intRow, int intCol, IIoTSensor recSensor)
{
    enforceRange(intRow, 0, _rows - 1);
    enforceRange(intCol, 0, _cols - 1);
    _sensors[intRow][intCol] = recSensor;
}

int IIoTMonitor::rangedRandom(int intLower, int intUpper) const
{
    int intRange = (intUpper - intLower) + 1;
    return rand() % intRange + intLower;
}

void IIoTMonitor::enforceRange(int intValue, int intMin, int intMax) const
{
    if(intValue < intMin || intValue > intMax)
    {
        cerr << "RANGE ERROR: " << intValue << " must be in [" << intMin << ", " << intMax << "]";
        exit(ERROR_RANGE);
    }
}





