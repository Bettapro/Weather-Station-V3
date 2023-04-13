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

#ifdef ESP8266

#if defined USE_ANALOG_LIGHT_SENSOR and ! defined(ANALOG_LIGHT_SENSOR_ADC_PIN)
    #define ANALOG_LIGHT_SENSOR_ADC_PIN ADC0 
#endif

#if defined USE_ANALOG_LIGHT_SENSOR and ! defined(ANALOG_LIGHT_SENSOR_POWER_PIN)
    #define ANALOG_LIGHT_SENSOR_POWER_PIN 14
#endif

#if defined USE_BH1750 and ! defined(BH1750_POWER_PIN)
    #define BH1750_POWER_PIN 14
#endif

#if defined USE_BME280 and ! defined(BME280_POWER_PIN)
    #define BME280_POWER_PIN 14
#endif

#if defined USE_DIGITAL_ANEMOMETER and ! defined(DIGITAL_ANEMOMETER_POWER_PIN)
    #define DIGITAL_ANEMOMETER_POWER_PIN 12
#endif

#if defined USE_DIGITAL_ANEMOMETER and ! defined(DIGITAL_ANEMOMETER_SIGNAL_PIN)
    #define DIGITAL_ANEMOMETER_SIGNAL_PIN 13
#endif

#if defined USE_BATTERY_SOC and ! defined(BATTERY_SOC_ADC_PIN)
    #define BATTERY_SOC_ADC_PIN A0
#endif


#endif