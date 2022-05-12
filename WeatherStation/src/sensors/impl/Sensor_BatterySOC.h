#ifndef SENSOR_BATTERYSOC_H
#define SENSOR_BATTERYSOC_H

#include "../Sensor.h"
#include "../SensorAvgRead.h"

#define BATT_SAMPLE_COUNT 2
#define BATT_SAMPLE_TIME 200

#include <Arduino.h>

class Sensor_BatterySOC : public Sensor
{
public:
    Sensor_BatterySOC(float vMax, float vMin, int8_t pinVoltage)
    {
        this->pinVoltage = pinVoltage;
        this->vMax = vMax;
        this->vMin = vMin;
    }
    const char *getName()
    {
        return "Battery SOC";
    }
    void start()
    {
        pinMode(this->pinVoltage, INPUT);
        this->ok = true;
    };
    bool setup()
    {
        return this->ok;
    };
    void readAll()
    {
        SensorAvgRead voltageAvg;
        for (uint8_t sampleCount = 0; sampleCount < BATT_SAMPLE_COUNT; sampleCount++)
        {
            float value = analogRead(this->pinVoltage) * vMax / 4095.0;
            voltageAvg.accumulate(value);
            delay(BATT_SAMPLE_TIME);
        }
        this->soc = (voltageAvg.get(vMin) - vMin) / (vMax - vMin) * 100;
    }

    void stop()
    {
    }

    float get(ReadingType what)
    {
        return this->has(what) ? this->soc : 0;
    }

    bool has(ReadingType what)
    {
        return what == ReadingType::RD_BATTERY_SOC && this->soc >= 0 && this->soc <= 100;
    }

private:
    float vMax;
    float vMin;
    int8_t pinVoltage;
    float soc;
};

#endif