
#pragma once 

#ifndef INCLUDE_ALL_LIB_H
#define INCLUDE_ALL_LIB_H

#if defined ESP32
#define USE_WIFI_NINA false
#define USE_WIFI101 false
#include <WiFi.h>
#elif defined ESP8266
#include <ESP8266WiFi.h>
#else
#error This board is not supported.
#endif

#include <LittleFS.h>

#include <Wire.h>

#define ESP_DRD_USE_LITTLEFS true
#include <ESP_DoubleResetDetector.h>     

// disable WM all logs
// #define WM_NODEBUG
#include <WiFiManager.h>

#include <ArduinoJson.h>



#endif