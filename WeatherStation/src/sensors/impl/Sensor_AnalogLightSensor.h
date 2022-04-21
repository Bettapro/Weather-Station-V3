#ifndef SENSOR_ANALOGLIGHSENSOR_H
#define SENSOR_ANALOGLIGHSENSOR_H

#include "../Sensor.h"
#include "../SensorAvgRead.h"

#define ANALOG_LIGH_SENSOR_SAMPLE_COUNT 5
#define ANALOG_LIGH_SENSOR_SAMPLE_TIME 100

#include <Arduino.h>

class Sensor_AnalogLightSensor : public Sensor
{
public:
    Sensor_AnalogLightSensor(uint8_t pinSignal, int8_t pinPower = -1)
    {
        this->pinSignal = pinSignal;
        this->pinPower = pinPower;
    }
    const char *getName()
    {
        return "Light sensor";
    }
    void start()
    {
        if (this->pinPower >= 0)
        {
            pinMode(this->pinPower, OUTPUT);
            digitalWrite(this->pinPower, 1);
        }
        pinMode(this->pinSignal, INPUT);
        this->ok = true;
    };
    bool setup()
    {
        return this->ok;
    };
    void readAll()
    {
        SensorAvgRead lightAvg;
        for (uint8_t sampleCount = 0; sampleCount < ANALOG_LIGH_SENSOR_SAMPLE_COUNT; sampleCount++)
        {
            // from https://arduinodiy.wordpress.com/2013/11/03/measuring-light-with-an-arduino/
            double Vout = analogRead(this->pinSignal) * 3.3 / 4095.0;
            if (Vout > 0 && Vout <= 3.3)
            {
                float lux = (500 * (3.3 - Vout)) / (10 * Vout);
                lightAvg.accumulate(lux);
            }
            delay(ANALOG_LIGH_SENSOR_SAMPLE_TIME);
        }
        this->lux = lightAvg.get(-1);
    }

    void stop()
    {
    }

    float get(ReadingType what)
    {
        return this->has(what) ? this->lux : 0;
    }

    bool has(ReadingType what)
    {
        return what == ReadingType::RD_LIGHT && this->lux >= 0 && this->lux <= 50000;
    }

private:
    uint8_t pinSignal;
    int8_t pinPower;
    float lux;
};

#endif