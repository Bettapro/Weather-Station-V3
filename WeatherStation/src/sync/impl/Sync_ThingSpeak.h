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

#ifndef SYNC_THINGSPEAK_H
#define SYNC_THINGSPEAK_H

#include "../../incl/include_all_lib.h"
#include "../Sync.h"
#include <ThingSpeak.h>

class Sync_ThingSpeak : public Sync
{
public:
    Sync_ThingSpeak(const char *apyKey, unsigned long channel)
    {
        this->apiKey = apiKey;
        this->channel = channel;
    };
    void setup()
    {
        this->client = new WiFiClient();
        ThingSpeak.begin(*this->client);
    };

    uint8_t flush()
    {
        if (this->light != nullptr)
        {
            ThingSpeak.setField(1, (int)round(*this->light));
        }
        if (this->temperature != nullptr)
        {
            ThingSpeak.setField(2, (float)(round(*this->temperature * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION));
        }
        if (this->humidity != nullptr)
        {
            ThingSpeak.setField(3, (float)(round(*this->humidity * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION));
        }
        if (this->pressure != nullptr)
        {
            ThingSpeak.setField(4, (int)round(*this->pressure));
        }
        if (this->windSpeed != nullptr)
        {
            ThingSpeak.setField(5, (int)round(*this->windSpeed));
        }
        if (this->batterySoc != nullptr)
        {
            ThingSpeak.setField(6, (float)(round(*this->batterySoc * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION));
        }
        int x = ThingSpeak.writeFields(this->channel, this->apiKey);
        return x == 200 ? 0 : 2;
    };

    void stop(){};

private:
    char *apiKey;
    unsigned long channel;
    //
    WiFiClient *client;
};

#endif