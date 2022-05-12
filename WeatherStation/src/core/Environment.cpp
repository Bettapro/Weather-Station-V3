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

#include "Environment.h"

#include "../incl/include_all_core.h"
#include "../incl/include_all_lib.h"

#include <string.h>

struct environrmentData Environment::envData;

void Environment::loadEnvData()
{

    // default from config.h
    envData.updateInterval = DEEP_SLEEP_FOR_SEC;

    strcpy(envData.wifiSSID, WIFI_SSID);
    strcpy(envData.wifiPassword, WIFI_PASS);

    strcpy(envData.wifiIp, WIFI_IP_ADDRESS);
    strcpy(envData.wifiGateway, WIFI_GATEWAY);
    strcpy(envData.wifiSubnet, WIFI_SUBNET);
    strcpy(envData.wifiDns1, WIFI_DNS1);
    strcpy(envData.wifiDns2, WIFI_DNS2);

    strcpy(envData.wmApSSID, WIFI_AP_CONFIGURATION_HOSTNAME);
    strcpy(envData.wmApPassword, WIFI_AP_CONFIGURATION_PASSWORD);

#ifdef USE_THINGSPEAK
    strcpy(envData.thingSpeakApiKey, THINGSPEAK_API_KEY);
    envData.thingSpeakChannel = THINGSPEAK_CHANNEL;
#endif

#ifdef USE_MQTT
    strcpy(envData.mqttServerHostname, MQTT_SERVER);
    strcpy(envData.mqttUsername, MQTT_USERNAME);
    strcpy(envData.mqttPassword, MQTT_PASSWORD);
    strcpy(envData.mqttClientId, MQTT_CLIENT_ID);
    envData.mqttServerPort = MQTT_PORT;
#ifdef USE_MQTT_HOME_ASSISTANT
    strcpy(envData.mqttHADeviceName, MQTT_HOME_ASSISTANT_DEVICE_NAME);
#endif
#endif
    if (!LittleFS.begin())
    {
        Environment::eraseAllData();
        if (!LittleFS.begin())
        {
            Serial.println("ERROR: cannot access to littlefs partition");
            return;
        }
    }
    // load from file
    if (!LittleFS.exists(CONFIG_PERSISTENCE))
    {
        // no file found
        Serial.println("No configuration file found");
    }
    else
    {
        Serial.println("Restoring configuration from file");
        // file exists, reading and loading
        File configFile = LittleFS.open(CONFIG_PERSISTENCE, "r");
        if (!configFile)
        {
            Serial.println("ERROR: cannot open config file");
        }
        else
        {
            size_t size = configFile.size();
            DynamicJsonDocument doc(size * 3);
            DeserializationError error = deserializeJson(doc, configFile);
            if (error)
            {
                Serial.println("ERROR: Cannot deserialize settings from file");
                Serial.println(error.c_str());
            }
            else
            {
                if (doc.containsKey(CONFIG_PERSISTENCE_STATION_UPDATE_INTERVAL_S))
                    envData.updateInterval = doc[CONFIG_PERSISTENCE_STATION_UPDATE_INTERVAL_S];

                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_SSID, envData.wifiSSID);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_PASSWORD, envData.wifiPassword);

                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_IP_ADDRESS, envData.wifiIp);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_GATEWAY, envData.wifiGateway);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_SUBNET, envData.wifiSubnet);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_DNS1, envData.wifiDns1);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WIFI_DNS2, envData.wifiDns2);

                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WM_AP_SSID, envData.wmApSSID);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_WM_AP_PASSWORD, envData.wmApPassword);

#ifdef USE_THINGSPEAK
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_THINGSPEAK_API_KEY, envData.thingSpeakApiKey);
                if (doc.containsKey(CONFIG_PERSISTENCE_THINGSPEAK_CHANNEL))
                    envData.thingSpeakChannel = doc[CONFIG_PERSISTENCE_THINGSPEAK_CHANNEL];
#endif

#ifdef USE_MQTT
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_MQTT_HOSTNAME, envData.mqttServerHostname);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_MQTT_PASSWORD, envData.mqttPassword);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_MQTT_USERNAME, envData.mqttUsername);
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_MQTT_CLIENT_ID, envData.mqttClientId);
                if (doc.containsKey(CONFIG_PERSISTENCE_MQTT_PORT))
                    envData.mqttServerPort = doc[CONFIG_PERSISTENCE_MQTT_PORT];

#endif
#ifdef USE_MQTT_HOME_ASSISTANT
                loadStringToEnvIfExist(doc, CONFIG_PERSISTENCE_MQTT_HA_DEVICE_NAME, envData.mqttHADeviceName);
#endif
            }
        }
    }
    LittleFS.end();
}

void Environment::loadStringToEnvIfExist(DynamicJsonDocument doc, const char *envKey, char *envValue)
{
    if (doc.containsKey(envKey))
        strcpy(envValue, doc[envKey]);
}

environrmentData *Environment::getData()
{
    return &envData;
}

void Environment::resetEnvData()
{
    LittleFS.begin();
    // load from file
    if (LittleFS.exists(CONFIG_PERSISTENCE))
    {
        LittleFS.remove(CONFIG_PERSISTENCE);
    }
    LittleFS.end();
}

void Environment::eraseAllData()
{
    LittleFS.format();
}