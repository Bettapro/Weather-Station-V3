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
    virtual uint8_t flush() = 0;
    virtual void stop() = 0;

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