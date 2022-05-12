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

#ifndef SENSORAVGREAD_H
#define SENSORAVGREAD_H

#include <Arduino.h>

class SensorAvgRead{
public:
    SensorAvgRead(){
        this->accumulator = this->count = 0;
    }

    void accumulate (float read, bool (*validation)(float)){
        if(validation(read)){
            this->accumulate(read);
        }
    }

    void accumulate(float read){
        this->accumulator += read;
        this->count ++;
    }
    float get(float defaultValue = 0){
        return this->count > 0 ? this->accumulator / this->count : defaultValue;
    }
private:
    float accumulator;
    uint8_t count;
};

#endif