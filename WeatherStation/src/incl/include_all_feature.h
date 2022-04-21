

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