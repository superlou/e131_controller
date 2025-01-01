# Programming the NodeMCU

1. Add the following to File -> Preferences -> Additional board manager URLs:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
2. From Boards Manager, install the esp8266 board package.
3. Select the NodeMCU 1.0, ESP-12E module.

# Libraries

To build, this requires:

* ESP Async E1.31
* ESPAsyncUDP (https://github.com/me-no-dev/ESPAsyncUDP) - needs to be manually downloaded into libraries
* FastLED