#ifndef SYNC_HA_H
#define SYNC_HA_H

#include "../../incl/include_all_lib.h"
#include "../Sync.h"
#include <ArduinoHA.h>

class Sync_HA : public Sync
{
public:
    Sync_HA(const char *server, const char *user, const char *password, const char *deviceId, const char *deviceName)
    {
        this->server = strdup(server);
        this->user = strdup(user);
        this->password = strdup(password);
        this->deviceId = strdup(deviceId);
        this->deviceName = strdup(deviceName);

        this->client = nullptr;
        this->device = nullptr;
        this->mqtt = nullptr;
    };

    void setup()
    {
        this->client = new WiFiClient();
        this->device = new HADevice(this->deviceId);
        this->mqtt = new HAMqtt(*this->client, *this->device);
        // set device's details (optional)
        this->device->setName(this->deviceName);
        this->device->setSoftwareVersion(PROJECT_VERSION);
        this->device->setModel(PROJECT_NAME);
        this->device->setManufacturer(PROJECT_AUTHOR);
    };

    uint8_t flush()
    {
        HASensor pressureSensor("pressure");
        pressureSensor.setDeviceClass("pressure");
        pressureSensor.setName("Atmoferic pressure");
        pressureSensor.setUnitOfMeasurement("hPa");

        HASensor lightSensor("light");

        lightSensor.setName("Light intensity");
        lightSensor.setUnitOfMeasurement("lx");
        lightSensor.setDeviceClass("illuminance");

        HASensor humidSensor("humidity");
        humidSensor.setName("Humidity");
        humidSensor.setDeviceClass("humidity");
        humidSensor.setUnitOfMeasurement("%");

        HASensor batterySensor("battery");
        batterySensor.setName("Battery SOC");
        batterySensor.setDeviceClass("battery");
        batterySensor.setUnitOfMeasurement("%");

        HASensor tempSensor("temperature");
        tempSensor.setName("Temperature");
        tempSensor.setUnitOfMeasurement("°C");

        HASensor windSensor("wind_speed");
        windSensor.setName("Wind speed");

        if (!this->mqtt->begin(this->server, this->user, this->password))
        {
            return 1;
        }

        this->mqtt->loop();

        int attemptCount = 0;
        while (!this->mqtt->isConnected())
        {
            if (attemptCount > 10)
            {
                return 2;
            }
            delay(100);
            this->mqtt->loop();
            attemptCount++;
        }

        pressureSensor.setAvailability(this->pressure != nullptr);
        if (this->pressure != nullptr)
        {
            pressureSensor.setValue((int)round(*this->pressure));
        }

        lightSensor.setAvailability(this->light != nullptr);
        if (this->light != nullptr)
        {
            lightSensor.setValue((int)round(*this->light));
        }

        humidSensor.setAvailability(this->humidity != nullptr);
        if (this->humidity != nullptr)
        {
            humidSensor.setValue(round(*this->humidity * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        batterySensor.setAvailability(this->batterySoc != nullptr);

        if (this->batterySoc != nullptr)
        {
            batterySensor.setValue(round(*this->batterySoc * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        tempSensor.setAvailability(this->temperature != nullptr);
        if (this->temperature != nullptr)
        {
            tempSensor.setValue(round(*this->temperature * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        windSensor.setAvailability(this->windSpeed != nullptr);
        if (this->windSpeed != nullptr)
        {
            windSensor.setValue((int)round(*this->windSpeed));
        }

        for (uint8_t index = 0; index < 5; index++)
        {
            this->mqtt->loop();
            delay(250);
        }
        return 0;
    };

    void stop()
    {
        if (this->mqtt != nullptr)
        {
            this->mqtt->disconnect();
            delete this->mqtt;
            this->mqtt = nullptr;
        }
        if (this->device != nullptr)
        {
            delete this->device;
            this->device = nullptr;
        }
        if (this->client != nullptr)
        {
            this->client->flush();
            delete this->client;
            this->client = nullptr;
        }
    }

private:
    char *server;
    char *user;
    char *password;
    char *deviceId;
    char *deviceName;
    //
    WiFiClient *client;
    HADevice *device;
    HAMqtt *mqtt;
};

#endif