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

#include <WiFiClient.h>

#include "../../incl/include_all_lib.h"
#include "../Sync.h"
#include "HomeAssistantArduinoMQTT.h"

class Sync_HA : public Sync {
    public:
        Sync_HA(const char* server, const char* user, const char* password, const char* deviceId, const char* deviceName) {
            this->server = strdup(server);
            this->user = strdup(user);
            this->password = strdup(password);
            this->deviceId = strdup(deviceId);
            this->deviceName = strdup(deviceName);

            this->ha = nullptr;
        }

        ~Sync_HA() {
            stop();
            free(this->server);
            free(this->user);
            free(this->password);
            free(this->deviceId);
            free(this->deviceName);
        }

        void setup(bool isDeepSleepWakeup) {
            this->ha = new HomeAssistantArduinoMQTT(7);

            this->ha->MqttUser = this->user;
            this->ha->MqttPassword = this->password;
            this->ha->Manufacturer = PROJECT_AUTHOR;
            this->ha->Model = PROJECT_NAME;
            this->ha->Version = PROJECT_VERSION;
            this->ha->HADeviceName = this->deviceName;
            this->ha->MQTTDeviceName = this->deviceId;
            this->ha->useSharedAvailability = false;

            this->ha->commandEnabled = false;

            this->ha->enableConfigPublishing = !isDeepSleepWakeup;

            this->ha->begin(this->client, this->server, 1883);
        }

        uint8_t flush() {
            if (this->ha == nullptr) return 1;

            this->ha->loop();

            int attemptCount = 0;
            while (!this->ha->connected()) {
                if (attemptCount > 50) {
                    return 2;
                }
                delay(100);
                this->ha->loop();
                attemptCount++;
            }

            HAEntityBuilder pBuilder = this->ha->newSensorEntity("pressure", "Atmospheric pressure");
            pBuilder.deviceClass("pressure");
            pBuilder.unit("hPa");
            pBuilder.suggestedDisplayPrecision(0);
            pBuilder.publish();

            HAEntityBuilder lBuilder = this->ha->newSensorEntity("light", "Light intensity");
            lBuilder.deviceClass("illuminance");
            lBuilder.unit("lx");
            lBuilder.suggestedDisplayPrecision(0);
            lBuilder.publish();

            HAEntityBuilder hBuilder = this->ha->newSensorEntity("humidity", "Humidity");
            hBuilder.deviceClass("humidity");
            hBuilder.unit("%");
            hBuilder.suggestedDisplayPrecision(1);
            hBuilder.publish();

            HAEntityBuilder bBuilder = this->ha->newSensorEntity("battery", "Battery SOC");
            bBuilder.deviceClass("battery");
            bBuilder.unit("%");
            bBuilder.suggestedDisplayPrecision(0);
            bBuilder.publish();

            HAEntityBuilder tBuilder = this->ha->newSensorEntity("temperature", "Temperature");
            tBuilder.deviceClass("temperature");
            tBuilder.unit("°C");
            tBuilder.suggestedDisplayPrecision(1);
            tBuilder.publish();

            HAEntityBuilder wBuilder = this->ha->newSensorEntity("wind_speed", "Wind speed");
            wBuilder.unit("km/h");
            wBuilder.suggestedDisplayPrecision(0);
            wBuilder.publish();

            /*
                        this->client.flush();
                        this->client.setNoDelay(true);
            */

            char valBuf[16];

            this->ha->setEntityAvailability("pressure", this->pressure != nullptr);
            if (this->pressure != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->pressure, 0);
                this->ha->setValue("pressure", valBuf);
            }

            this->ha->setEntityAvailability("light", this->light != nullptr);
            if (this->light != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->light, 1);
                this->ha->setValue("light", valBuf);
            }

            this->ha->setEntityAvailability("humidity", this->humidity != nullptr);
            if (this->humidity != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->humidity, 1);
                this->ha->setValue("humidity", valBuf);
            }

            this->ha->setEntityAvailability("battery", this->batterySoc != nullptr);
            if (this->batterySoc != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->batterySoc, 0);
                this->ha->setValue("battery", valBuf);
            }

            this->ha->setEntityAvailability("temperature", this->temperature != nullptr);
            if (this->temperature != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->temperature, 2);
                this->ha->setValue("temperature", valBuf);
            }

            this->ha->setEntityAvailability("wind_speed", this->windSpeed != nullptr);
            if (this->windSpeed != nullptr) {
                HAAM_FORMAT_FLOAT(valBuf, *this->windSpeed, 0);
                this->ha->setValue("wind_speed", valBuf);
            }

            this->ha->sendValues();

            for (uint8_t index = 0; index < 3; index++) {
                this->ha->loop();
                delay(50);
            }
            return 0;
        }

        void stop() {
            if (this->ha != nullptr) {
                delete this->ha;
                this->ha = nullptr;
            }
            this->client.stop();
        }

    private:
        char* server;
        char* user;
        char* password;
        char* deviceId;
        char* deviceName;

        WiFiClient client;
        HomeAssistantArduinoMQTT* ha;
};

#endif