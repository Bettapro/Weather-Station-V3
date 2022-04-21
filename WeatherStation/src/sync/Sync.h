#ifndef SYNC_H
#define SYNC_H

#include <stdlib.h> 
#include "../sensors/Sensor.h"

class Sync
{
public:
    virtual void setup() = 0;
    virtual void load(ReadingType type, float value)
    {
        memcpy(this->getOrAlloc(type), &value, sizeof(float));
    }
    virtual bool flush() = 0;

protected:
    float *light = nullptr;
    float *pressure = nullptr;
    float *humidity = nullptr;
    float *batterySoc = nullptr;
    float *windSpeed = nullptr;
    float *temperature = nullptr;

private:
    float *getOrAlloc(ReadingType type)
    {
        switch (type)
        {
        case RD_LIGHT:
            return this->light == nullptr ? this->light = (float*)malloc(sizeof(float)) : this->light;
        case RD_PRESSURE:
            return this->pressure == nullptr ? this->pressure = (float*)malloc(sizeof(float)) : this->pressure;
        case RD_HUMIDITY:
            return this->humidity == nullptr ? this->humidity = (float*)malloc(sizeof(float)) : this->humidity;
        case RD_BATTERY_SOC:
            return this->batterySoc == nullptr ? this->batterySoc = (float*)malloc(sizeof(float)) : this->batterySoc;
        case RD_WIND_SPEED:
            return this->windSpeed == nullptr ? this->windSpeed = (float*)malloc(sizeof(float)) : this->windSpeed;
        case RD_TEMPERATURE:
            return this->temperature == nullptr ? this->temperature = (float*)malloc(sizeof(float)) : this->temperature;
        }
        return nullptr;
    }
};

#endif