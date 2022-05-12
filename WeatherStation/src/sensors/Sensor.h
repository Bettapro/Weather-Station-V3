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