# Weather-Station-V3
Create your own weather station with an esp8266/ESP32 and monitor temperature, wind speed..and more.

This project comes from a blog I found sometime ago, the purpose is to build a DIY weather station by using some simple components and a 3d printer.
The weather station connect to a existing WIFI network and sends updates about the weather, it's powered with a battery (charged via a small solar panel).

Here the original articles:
- [PART 1](https://www.the-diy-life.com/diy-3d-printed-iot-weather-station-using-an-esp32/)
- [PART 2](https://www.the-diy-life.com/i-upgraded-my-3d-printed-weather-station-using-your-suggestions)

I redesigned the sketch developed by the author to make it more customizable and to integrate it with Home Assistant (and others?).
Most of the common parameters (wifi setting, networking settings, update interval ..) could be changed via a web interface without recompiling the firmware on each modification


The weather station can provide data of:
- Temperature (°C)
- Humidity (%)
- Light intensity (lx)
- Atmospheric pressure (hPa)
- Battery percentage (%)
- Wind speed (Km/h)

Boards supported:
- ESP8266
- ESP32

Compatible sensor modules:
- BME280 (temperature, atmospheric pressure, humidity)
- BH1750 (light intensity)
- Allegro A3213/A3144 Hall Effect Sensor (wind speed)
- Reed Switch (wind speed)

Platform/Integration supported:
- Thingspeak
- MQTT (general purpose)
- Home Assistant - MQTT integration



