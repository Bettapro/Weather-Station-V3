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