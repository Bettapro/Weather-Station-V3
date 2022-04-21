#ifndef SENSOR_H
#define SENSOR_H

#define RAW_MEASURE_PRECISION 10.00


typedef enum
{
        RD_LIGHT,
        RD_WIND_SPEED,
        RD_TEMPERATURE,
        RD_PRESSURE,
        RD_HUMIDITY,
        RD_BATTERY_SOC,
        //
        RD_COUNT
} ReadingType;

class Sensor{
public:
    

    virtual const char* getName();
    virtual void start() = 0;
    virtual bool setup() = 0;
    virtual void readAll() = 0;
    virtual void stop() = 0;
    virtual float get(ReadingType what) = 0;
    virtual bool has(ReadingType what) = 0;
    bool isOk(){
        return this->ok;
    };

protected:
    bool ok = false;
};


#endif