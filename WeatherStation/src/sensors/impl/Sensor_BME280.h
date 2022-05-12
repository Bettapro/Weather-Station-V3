/**
 * Weather station V3 [https://github.com/Bettapro/Weather-Station-V3]
 * Copyright (c) 2022 Alberto Bettin
 *
 * Based on the work of Michael Klements from "The DIY Life"
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef SENSOR_BME280_H
#define SENSOR_BME280_H

#include "../Sensor.h"
#include "../SensorAvgRead.h"

#include <Adafruit_BME280.h>

#define SAMPLE_COUNT 5
#define SAMPLE_TIME 100

class Sensor_BME280 : public Sensor
{
public:
    Sensor_BME280(byte addr, int8_t pin = -1)
    {
        this->bme = new Adafruit_BME280();
        this->pin = pin;
        this->address = addr;
    }
    const char *getName()
    {
        return "BME280";
    }
    void start()
    {
        if (this->pin >= 0)
        {
            digitalWrite(this->pin, HIGH);
        }
    };
    bool setup()
    {
        return this->ok = this->bme->begin(address);
    };
    void readAll()
    {
        SensorAvgRead pressureAvg;
        SensorAvgRead humidityAvg;
        SensorAvgRead temperatureAvg;
        for (uint8_t sampleCount = 0; sampleCount < SAMPLE_COUNT; sampleCount++)
        {
            temperatureAvg.accumulate(bme->readTemperature(), [](float v)
                                      { return v >= -40 && v <= 85; });
            humidityAvg.accumulate(bme->readHumidity(), [](float v)
                                   { return v >= 0 && v <= 100; });
            pressureAvg.accumulate(bme->readPressure() / 100.0, [](float v)
                                   { return v >= 300 && v <= 1100; });
            delay(SAMPLE_TIME);
        }
        this->pressure = pressureAvg.get(-1);
        this->humidity = humidityAvg.get(-1);
        this->temperature = temperatureAvg.get(-999);
    }

    void stop()
    {
        if (this->pin >= 0)
        {
            pinMode(this->pin, OUTPUT);
            digitalWrite(this->pin, LOW);
        }
    }

    float get(ReadingType what)
    {
        if (this->has(what))
        {
            switch (what)
            {
            case RD_TEMPERATURE:
                return this->temperature;
            case RD_PRESSURE:
                return this->pressure;
            case RD_HUMIDITY:
                return this->humidity;
            }
        }
        return 0;
    }

    bool has(ReadingType what)
    {
        switch (what)
        {
        case RD_TEMPERATURE:
            return this->temperature >= -40;
        case RD_PRESSURE:
            return this->pressure >= 0;
        case RD_HUMIDITY:
            return this->humidity >= 0;
        }
        return false;
    }

private:
    Adafruit_BME280 *bme;
    byte address;
    int8_t pin;
    float pressure;
    float humidity;
    float temperature;
};

#endif