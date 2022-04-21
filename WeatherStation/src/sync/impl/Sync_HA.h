#ifndef SYNC_HA_H
#define SYNC_HA_H

#include "../../incl/include_all_lib.h"
#include "../Sync.h"
#include <ArduinoHA.h>


class Sync_HA : public Sync
{
public:
    Sync_HA(const char *server, const char *user, const char *password, const char *deviceId, const char * deviceName)
    {
        this->server = strdup(server);
        this->user = strdup(user);
        this->password = strdup(password);
        this->deviceId = strdup(deviceId);
        this->deviceName = strdup(deviceName);
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
         this->device->setManufacturer(PROJECT_NAME);
    };

    bool flush()
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
            return false;
        }

        this->mqtt->loop();

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

        for (uint16_t index = 0; index < 15; index++)
        {
            this->mqtt->loop();
            delay(100);
        }

        return true;
    };

private:
    char *server;
    char *user;
    char *password;
    char *deviceId;
    char * deviceName;
    //
    WiFiClient *client;
    HADevice *device;
    HAMqtt *mqtt;
};

#endif