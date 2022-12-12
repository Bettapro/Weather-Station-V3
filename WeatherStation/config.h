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

#define SERIAL_DEBUG_BAUDRATE 115200


/*
 * WIFI

 * Fill with you wifi auth. data
 */
// your wifi SSID
#define WIFI_SSID             "-your-wifi-"
// your wifi PASSWORD
#define WIFI_PASS             "-your-password-"
// your wifi IP ADDRESS
#define WIFI_IP_ADDRESS       ""
// your wifi GATEWAY
#define WIFI_GATEWAY          ""
// your wifi SUBNET
#define WIFI_SUBNET           ""
// your wifi DNS1
#define WIFI_DNS1             ""
// your wifi DNS2
#define WIFI_DNS2             ""

#define WIFI_AP_CONFIGURATION_HOSTNAME "WeatherAP"
#define WIFI_AP_CONFIGURATION_PASSWORD "admin1234"

#define DEEP_SLEEP_FOR_SEC 500

//#define USE_ANALOG_LIGHT_SENSOR
#ifdef USE_ANALOG_LIGHT_SENSOR
  //#define ANALOG_LIGHT_SENSOR_ADC_PIN 36

  //#define ANALOG_LIGHT_SENSOR_POWER_PIN 19
#endif

#define USE_BH1750
#ifdef USE_BH1750
  #define BH1750_I2C_ADDRESS 0x23

  //#define BH1750_POWER_PIN 19
#endif

#define USE_BME280
#ifdef USE_BME280
  #define BME280_I2C_ADDRESS 0x76

  //#define BME280_POWER_PIN 19
#endif

#define USE_DIGITAL_ANEMOMETER
#ifdef USE_DIGITAL_ANEMOMETER
  //#define DIGITAL_ANEMOMETER_POWER_PIN 18

  //#define DIGITAL_ANEMOMETER_SIGNAL_PIN 23
#endif

#define USE_BATTERY_SOC
#ifdef USE_BATTERY_SOC
    //#define BATTERY_SOC_ADC_PIN 34

    #define BATTERY_SOC_MAX_VOLTAGE 4.54

    #define BATTERY_SOC_MIN_VOLTAGE 3.3

    #define BATTERY_SOC_MIN_THROTTLE_SOC 30

    #define BATTERY_SOC_MIN_SOC 5
#endif

//#define USE_THINGSPEAK
#if defined(USE_THINGSPEAK)
  #define THINGSPEAK_CHANNEL 1

  #define THINGSPEAK_API_KEY "--api-key---"
#endif

#define USE_MQTT
#if defined (USE_MQTT)
  //address of mqtt server (specify the hostname or the ip address eg: IPAddress(192, 168, 1, 78) )
  #define MQTT_SERVER "127.0.0.1"
  // port number of the mqtt server (eg: 1883)
  #define MQTT_PORT 1883
  // username to use 
  #define MQTT_USERNAME "user"
  // password to use in combination with MQTT_USERNAME
  #define MQTT_PASSWORD "password"
  // client id
  #define MQTT_CLIENT_ID "weatherstation1"

  #define USE_MQTT_HOME_ASSISTANT
  #ifdef USE_MQTT_HOME_ASSISTANT
    #define MQTT_HOME_ASSISTANT_DEVICE_NAME "Weather-station01"
  #endif
 #endif