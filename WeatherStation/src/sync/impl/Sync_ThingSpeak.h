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

    bool flush()
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
        return x == 200;
    };

private:
    char *apiKey;
    unsigned long channel;
    //
    WiFiClient *client;
};

#endif