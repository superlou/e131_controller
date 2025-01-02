#include <ESP8266WiFi.h>
#include <ESPAsyncE131.h>

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>    // Using 3.4.0

#define NUM_LEDS 60
#define DATA_PIN 4

#include "controller_config.h"
#include "config_server.h"

ControllerConfig config;
ConfigServer config_server(&config);

CRGB leds[NUM_LEDS];

const char *ssid = "meta_2g4";
const char *password = "galactica";

#define UNIVERSE 1
#define UNIVERSE_COUNT 1

ESPAsyncE131 e131(UNIVERSE_COUNT);

void setup() {
  Serial.begin(115200);
  delay(100);

  config.global_brightness = 80;

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setDither(0);
  
  Serial.println("\n");
  Serial.println("Started...\n");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }

  Serial.print("connected.\n");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT)) {
    Serial.println(F("Listening for data..."));
  } else {
    Serial.println(F("*** e131.begin failed ***"));
  }

  config_server.start();
}

void loop() {
  config_server.handle_client();
  
  while (!e131.isEmpty()) {
    e131_packet_t packet;
    e131.pull(&packet);     // Pull packet from ring buffer
    
    /*Serial.printf("Universe %u / %u Channels | Packet#: %u / Errors: %u / CH1: %u\n",
            htons(packet.universe),                 // The Universe for this packet
            htons(packet.property_value_count) - 1, // Start code is ignored, we're interested in dimmer data
            e131.stats.num_packets,                 // Packet counter
            e131.stats.packet_errors,               // Packet error counter
            packet.property_values[1]);             // Dimmer data for Channel 1*/

    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(packet.property_values[i*3 + 1], packet.property_values[i*3 + 2], packet.property_values[i*3 + 3]);
    }
  }

  FastLED.setBrightness(config.global_brightness);
  FastLED.show();
  delay(10);
}
