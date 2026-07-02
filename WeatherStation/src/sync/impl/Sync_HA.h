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

#ifndef SYNC_HA_H
#define SYNC_HA_H

#include "../../incl/include_all_lib.h"
#include "../Sync.h"
#include <ArduinoHA.h>
#include <math.h> // roundf()

#define MAX_HA_SENSORS 7

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

        this->pressureSensor = nullptr;
        this->lightSensor = nullptr;
        this->humidSensor = nullptr;
        this->batterySensor = nullptr;
        this->tempSensor = nullptr;
        this->windSensor = nullptr;
    }

    ~Sync_HA()
    {
        stop(); 
        free(this->user);
        free(this->password);
        free(this->deviceId);
        free(this->deviceName);
    }

    void setup()
    {
        this->client = new WiFiClient();
        this->device = new HADevice(this->deviceId);
        this->mqtt = new HAMqtt(*this->client, *this->device, MAX_HA_SENSORS);
        
        // set device's details (optional)
        this->device->setName(this->deviceName);
        this->device->setSoftwareVersion(PROJECT_VERSION);
        this->device->setModel(PROJECT_NAME);
        this->device->setManufacturer(PROJECT_AUTHOR);


        this->pressureSensor = new HASensorNumber("pressure");
        this->pressureSensor->setDeviceClass("pressure");
        this->pressureSensor->setName("Atmospheric pressure"); // Corretto il refuso
        this->pressureSensor->setUnitOfMeasurement("hPa");

        this->lightSensor = new HASensorNumber("light", HABaseDeviceType::PrecisionP0);
        this->lightSensor->setName("Light intensity");
        this->lightSensor->setUnitOfMeasurement("lx");
        this->lightSensor->setDeviceClass("illuminance");

        this->humidSensor = new HASensorNumber("humidity", HABaseDeviceType::PrecisionP1);
        this->humidSensor->setName("Humidity");
        this->humidSensor->setDeviceClass("humidity");
        this->humidSensor->setUnitOfMeasurement("%");

        this->batterySensor = new HASensorNumber("battery", HABaseDeviceType::PrecisionP0);
        this->batterySensor->setName("Battery SOC");
        this->batterySensor->setDeviceClass("battery");
        this->batterySensor->setUnitOfMeasurement("%");

        this->tempSensor = new HASensorNumber("temperature", HABaseDeviceType::PrecisionP1);
        this->tempSensor->setName("Temperature");
        this->tempSensor->setDeviceClass("temperature");
        this->tempSensor->setUnitOfMeasurement("°C");

        this->windSensor = new HASensorNumber("wind_speed", HABaseDeviceType::PrecisionP0);
        this->windSensor->setName("Wind speed");
        this->windSensor->setUnitOfMeasurement("km/h");
    }

    uint8_t flush()
    {
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
        this->client->setNoDelay(true);

        bool syncOk = true;

        this->pressureSensor->setAvailability(this->pressure != nullptr);
        if (syncOk && this->pressure != nullptr)
        {
            syncOk &= this->pressureSensor->setValue(*this->pressure);
        }

        this->lightSensor->setAvailability(this->light != nullptr);
        if (syncOk && this->light != nullptr)
        {
            syncOk &= this->lightSensor->setValue(*this->light);
        }

        this->humidSensor->setAvailability(this->humidity != nullptr);
        if (syncOk && this->humidity != nullptr)
        {
            // Logica di arrotondamento corretta (es. 12.345 * 10 -> 123.45 -> round(123) -> 123.0 / 10 -> 12.3)
            syncOk &= this->humidSensor->setValue(roundf(*this->humidity * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        this->batterySensor->setAvailability(this->batterySoc != nullptr);
        if (syncOk && this->batterySoc != nullptr)
        {
            syncOk &= this->batterySensor->setValue(roundf(*this->batterySoc * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        this->tempSensor->setAvailability(this->temperature != nullptr);
        if (syncOk && this->temperature != nullptr)
        {
            syncOk &= this->tempSensor->setValue(roundf(*this->temperature * RAW_MEASURE_PRECISION) / RAW_MEASURE_PRECISION);
        }

        this->windSensor->setAvailability(this->windSpeed != nullptr);
        if (syncOk && this->windSpeed != nullptr)
        {
            syncOk &= this->windSensor->setValue(*this->windSpeed);
        }

        for (uint8_t index = 0; index < 3; index++)
        {
            this->mqtt->loop();
            delay(50);
        }
        return syncOk ? 0 : 10;
    }

    void stop()
    {
        // Deallocazione dei sensori
        if (this->pressureSensor != nullptr) { delete this->pressureSensor; this->pressureSensor = nullptr; }
        if (this->lightSensor != nullptr) { delete this->lightSensor; this->lightSensor = nullptr; }
        if (this->humidSensor != nullptr) { delete this->humidSensor; this->humidSensor = nullptr; }
        if (this->batterySensor != nullptr) { delete this->batterySensor; this->batterySensor = nullptr; }
        if (this->tempSensor != nullptr) { delete this->tempSensor; this->tempSensor = nullptr; }
        if (this->windSensor != nullptr) { delete this->windSensor; this->windSensor = nullptr; }

        // Deallocazione delle connessioni
        if (this->mqtt != nullptr)
        {
            this->mqtt->loop();
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
    
    WiFiClient *client;
    HADevice *device;
    HAMqtt *mqtt;

    HASensorNumber *pressureSensor;
    HASensorNumber *lightSensor;
    HASensorNumber *humidSensor;
    HASensorNumber *batterySensor;
    HASensorNumber *tempSensor;
    HASensorNumber *windSensor;
};

#endif