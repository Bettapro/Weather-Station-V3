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

#ifndef INCLUDE_ALL_FEATURE_H
#define INCLUDE_ALL_FEATURE_H

#include "include_all_core.h"

#include "../core/Environment.h"


#include "../feature/wifi_manager.h"

#include "../sensors/Sensor.h"
#ifdef USE_BH1750
#include "../sensors/impl/Sensor_BH1750.h"
#endif
#ifdef USE_ANALOG_LIGHT_SENSOR
#include "../sensors/impl/Sensor_AnalogLightSensor.h"
#endif
#ifdef USE_BME280
#include "../sensors/impl/Sensor_BME280.h"
#endif
#ifdef USE_DIGITAL_ANEMOMETER
#include "../sensors/impl/Sensor_DigitalAnemometer.h"
#endif
#ifdef USE_BATTERY_SOC
#include "../sensors/impl/Sensor_BatterySOC.h"
#endif

#include "../sync/Sync.h"
#ifdef USE_MQTT_HOME_ASSISTANT
#include "../sync/impl/Sync_HA.h"
#endif
#ifdef USE_THINGSPEAK
#include "../sync/impl/Sync_ThingSpeak.h"
#endif

#endif