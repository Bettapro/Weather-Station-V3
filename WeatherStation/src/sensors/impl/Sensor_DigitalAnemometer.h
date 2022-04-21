#ifndef SENSOR_DIGITALANEMOMETER_H
#define SENSOR_DIGITALANEMOMETER_H

#include "../Sensor.h"

#include <Arduino.h>

class Sensor_DigitalAnemometer : public Sensor
{
public:
    Sensor_DigitalAnemometer(uint8_t pinSignal, int8_t pinPower = -1)
    {
        this->pinSignal = pinSignal;
        this->pinPower = pinPower;
    }
    const char* getName(){
        return "Dig. Anemometer";
    }
    void start()
    {
        if (this->pinPower >= 0)
        {
            pinMode(this->pinPower, OUTPUT);
            digitalWrite(this->pinPower, HIGH);
        }
         pinMode(this->pinSignal, INPUT_PULLUP);
         this->ok = true;
    };
    bool setup()
    {
        return this->ok;
    };
    void readAll()
    {
        int counter = 0; // Counter to keep track of the number of wind speed revolutions
        int lastState = 0; // Variable to store the last state of wind sensor input
        for (int i = 0; i <= 6000; i++)
        {
            int readW = digitalRead(this->pinSignal);
            if (readW == HIGH && lastState == 0)
            {
                counter++;
                lastState = 1;
            }
            else if (readW == LOW && lastState == 1)
            {
                lastState = 0;
            }
            delay(1);
        }
        int ave = 2000;
        if (counter > 1) // Check that at least two ticks have been registered, one is meaningless
        {
            ave = 6000 / (counter - 1); // Calculate the average time between ticks
        }
        //Serial.print("Average Tick Time: ");
        //Serial.println(ave);
        if (ave < 28) // Discard readings faster than 102kph
            ave = 28;
        int index = 0;
        while (ave < windMap[0][index]) // Search through the windMap array for the corressponding wind value
            index++;
        this->wind = windMap[1][index];
    }

    void stop()
    {
        if (this->pinPower >= 0)
        {
            digitalWrite(this->pinPower, LOW);
        }
    }

    float get(ReadingType what)
    {
        return this->has(what) ? this->wind : 0;
    }

    bool has(ReadingType what)
    {
        return what == ReadingType::RD_WIND_SPEED;
    }

private:
    uint8_t pinSignal;
    int8_t pinPower;
    uint8_t wind;
    int windMap[2][32] = {{2000,1400,1000,600,500,400,320,280,240,220,200,180,170,160,150,140,130,120,110,100,90,80,70,60,50,40,38,36,34,32,30,28},{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,20,23,25,29,34,41,51,54,57,60,64,68,73}};

};

#endif