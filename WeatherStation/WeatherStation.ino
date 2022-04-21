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

#include "src/incl/include_all_core.h"
#include "src/incl/include_all_lib.h"
#include "src/incl/include_all_feature.h"

#include <vector>

#define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds

DoubleResetDetector *drd;

void setup() // Setup function - only function that is run in deep sleep mode
{
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  Environment::loadEnvData();
  const environrmentData *envData = Environment::getData();

  IPAddress ip;
  IPAddress gateway;
  IPAddress subnet;
  IPAddress dns1;
  IPAddress dns2;

  if (strlen(envData->wifiIp))
  {
    ip.fromString(envData->wifiIp);
  }

  if (strlen(envData->wifiGateway))
  {
    gateway.fromString(envData->wifiGateway);
  }
  if (strlen(envData->wifiSubnet))
  {
    subnet.fromString(envData->wifiSubnet);
  }
  if (strlen(envData->wifiDns1))
  {
    dns1.fromString(envData->wifiDns1);
  }
  if (strlen(envData->wifiDns2))
  {
    dns1.fromString(envData->wifiDns2);
  }

  drd = new DoubleResetDetector(2, 0);

  if (drd->detectDoubleReset())
  {
    drd->stop();
    Serial.println("Double Reset Detected");

    WiFi.config(ip, gateway, subnet, dns1, dns2);
    WiFi.begin(Environment::getData()->wifiSSID, Environment::getData()->wifiPassword);

    WifiManagerWB::startWifiConfigurationAP(true);
    ESP.restart();
  }

  esp_sleep_enable_timer_wakeup(envData->updateInterval * uS_TO_S_FACTOR); // Initialise deep sleep mode parameters

  std::vector<Sensor *> sensors;

#ifdef USE_ANALOG_LIGHT_SENSOR
  Sensor_AnalogLightSensor lightSensor(ANALOG_LIGHT_SENSOR_ADC_PIN, ANALOG_LIGHT_SENSOR_POWER_PIN);
  sensors.push_back(&lightSensor);
#endif

#ifdef USE_BH1750
  Sensor_BH1750 bh1750(BH1750_I2C_ADDRESS, BH1750_POWER_PIN);
  sensors.push_back(&bh1750);
#endif

#ifdef USE_BME280
  Sensor_BME280 bme280(BME280_I2C_ADDRESS, BME280_POWER_PIN);
  sensors.push_back(&bme280);
#endif

#ifdef USE_DIGITAL_ANEMOMETER
  Sensor_DigitalAnemometer anemometer(DIGITAL_ANEMOMETER_SIGNAL_PIN, DIGITAL_ANEMOMETER_POWER_PIN);
  sensors.push_back(&anemometer);
#endif

#ifdef USE_BATTERY_SOC
  Sensor_BatterySOC battery(BATTERY_SOC_MAX_VOLTAGE, BATTERY_SOC_MIN_VOLTAGE, BATTERY_SOC_ADC_PIN);
  sensors.push_back(&battery);
#endif

#ifdef USE_THINGSPEAK
  Sync_ThingSpeak syncTS(envData->thingSpeakApiKey, envData->thingSpeakChannel);
#endif
#ifdef USE_MQTT_HOME_ASSISTANT
  Sync_HA syncHa(envData->mqttServerHostname, envData->mqttUsername, envData->mqttPassword, envData->mqttClientId, envData->mqttHADeviceName);
#endif

  for (const auto &sensor : sensors)
  {
    sensor->start();
  }
  delay(500);
  drd->loop();
  Wire.begin();
  for (const auto &sensor : sensors)
  {
    if (!sensor->setup())
    {
      Serial.print("Error while setting up ");
      Serial.println(sensor->getName());
    }
  }

  float cValue;
  for (const auto &sensor : sensors)
  {
    Serial.print("Reading from ");
    Serial.println(sensor->getName());

    sensor->readAll();
    for (uint8_t rdi = 0; rdi <= RD_COUNT; rdi++)
    {
      ReadingType rd = (ReadingType)rdi;
      if (sensor->isOk() && sensor->has(rd))
      {
        cValue = sensor->get(rd);
        switch (rd)
        {
        case RD_BATTERY_SOC:
          Serial.print("Battery SOC");
          break;
        case RD_HUMIDITY:
          Serial.print("Humidity");
          break;
        case RD_LIGHT:
          Serial.print("Light intensity");
          break;
        case RD_PRESSURE:
          Serial.print("Pressure");
          break;
        case RD_TEMPERATURE:
          Serial.print("Temperature");
          break;
        case RD_WIND_SPEED:
          Serial.print("Wind speed");
          break;
        default:
          Serial.print("????");
          break;
        }
        Serial.print(": ");
        Serial.println(cValue);
#ifdef USE_MQTT_HOME_ASSISTANT
        syncHa.load(rd, cValue);
#endif
#ifdef USE_THINGSPEAK
        syncTS.load(rd, cValue);
#endif
      }
    }
    drd->loop();
  }
  for (const auto &sensor : sensors)
  {
    sensor->stop();
  }

  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(Environment::getData()->wifiSSID, Environment::getData()->wifiPassword);

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20)
  {
    delay(500);
    Serial.print(".");
    timeout++;
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi connected");
#ifdef USE_THINGSPEAK
    syncTS.setup();
    if (!syncTS.flush())
    {
      Serial.println("Sync ERROR with ThingSpeak");
    }
#endif
#ifdef USE_MQTT_HOME_ASSISTANT
    syncHa.setup();
    if (!syncHa.flush())
    {
      Serial.println("Sync ERROR with HA");
    }
#endif
  }
  else
  {
    Serial.println("");
    Serial.println("WiFi connection failed");
  }

  drd->loop();

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start(); // Enter sleep mode
}

void loop() // Loop function - unused
{
}
