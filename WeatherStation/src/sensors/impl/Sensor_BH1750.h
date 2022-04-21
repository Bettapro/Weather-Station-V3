#ifndef SENSOR_BH1750_H
#define SENSOR_BH1750_H

#include "../Sensor.h"
#include "../SensorAvgRead.h"

#include <BH1750.h>

#define SAMPLE_COUNT 5
#define SAMPLE_TIME 100

class Sensor_BH1750 : public Sensor
{
public:
    Sensor_BH1750(byte addr, int8_t pin = -1)
    {
        this->lightMeter = new BH1750(addr);
        this->pin = pin;
    }
    const char *getName()
    {
        return "BH1750";
    }
    void start()
    {
        if (this->pin >= 0)
        {
            pinMode(this->pin, OUTPUT);
            digitalWrite(this->pin, HIGH);
        }
    };
    bool setup()
    {
        return this->ok = this->lightMeter->begin();
    };
    void readAll()
    {
        SensorAvgRead lightAvg;
        for (uint8_t sampleCount = 0; sampleCount < SAMPLE_COUNT; sampleCount++)
        {
            lightAvg.accumulate(lightMeter->readLightLevel(), [](float v)
                                { return v >= 0 && v <= 65535; });
            delay(SAMPLE_TIME);
        }
        this->lightIntensity = lightAvg.get(-1);
    }

    void stop()
    {
        if (this->pin >= 0)
        {
            digitalWrite(this->pin, LOW);
        }
    }

    float get(ReadingType what)
    {
        return this->has(what) ? this->lightIntensity : 0;
    }

    bool has(ReadingType what)
    {
        return what == ReadingType::RD_LIGHT && this->lightIntensity >= 0;
    }

private:
    BH1750 *lightMeter;
    int8_t pin;
    float lightIntensity;
};

#endif