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

#pragma once

#define CONFIG_PERSISTENCE "/config.json"

#define CONFIG_PERSISTENCE_WIFI_SSID "ssid"
#define CONFIG_PERSISTENCE_WIFI_SSID_LEN 20

#define CONFIG_PERSISTENCE_WIFI_PASSWORD "passw"
#define CONFIG_PERSISTENCE_WIFI_PASSWORD_LEN 30

#define CONFIG_PERSISTENCE_WM_AP_SSID "wmSsid"
#define CONFIG_PERSISTENCE_WM_AP_SSID_LEN 15

#define CONFIG_PERSISTENCE_WM_AP_PASSWORD "wmPassw"
#define CONFIG_PERSISTENCE_WM_AP_PASSWORD_LEN 30

#define CONFIG_PERSISTENCE_THINGSPEAK_API_KEY "tgsApi"
#define CONFIG_PERSISTENCE_THINGSPEAK_API_KEY_LEN 16

#define CONFIG_PERSISTENCE_THINGSPEAK_CHANNEL "tgsChan"

#define CONFIG_PERSISTENCE_MQTT_HOSTNAME "mqttSrv"
#define CONFIG_PERSISTENCE_MQTT_HOSTNAME_LEN 20

#define CONFIG_PERSISTENCE_MQTT_PORT "mqttPort"

#define CONFIG_PERSISTENCE_MQTT_CLIENT_ID "mqttClnt"
#define CONFIG_PERSISTENCE_MQTT_CLIENT_ID_LEN 15

#define CONFIG_PERSISTENCE_MQTT_USERNAME "mqttUsr"
#define CONFIG_PERSISTENCE_MQTT_USERNAME_LEN 15

#define CONFIG_PERSISTENCE_MQTT_PASSWORD "mqttPassw"
#define CONFIG_PERSISTENCE_MQTT_PASSWORD_LEN 15

#define CONFIG_PERSISTENCE_MQTT_HA_DEVICE_NAME "haDeviceName"
#define CONFIG_PERSISTENCE_MQTT_HA_DEVICE_NAME_LEN 20

#define CONFIG_PERSISTENCE_WIFI_IP_ADDRESS "ipAddr"
#define CONFIG_PERSISTENCE_WIFI_IP_ADDRESS_LEN 15

#define CONFIG_PERSISTENCE_WIFI_SUBNET "subnet"
#define CONFIG_PERSISTENCE_WIFI_SUBNET_LEN 15

#define CONFIG_PERSISTENCE_WIFI_GATEWAY "gateway"
#define CONFIG_PERSISTENCE_WIFI_GATEWAY_LEN 15

#define CONFIG_PERSISTENCE_WIFI_DNS1 "dns1"
#define CONFIG_PERSISTENCE_WIFI_DNS1_LEN 15

#define CONFIG_PERSISTENCE_WIFI_DNS2 "dns2"
#define CONFIG_PERSISTENCE_WIFI_DNS2_LEN 15

#define CONFIG_PERSISTENCE_STATION_UPDATE_INTERVAL_S "wstUpdateS"
