#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID     "ADN-IOT"        
#define WIFI_PASSWORD "WBNuyawB2a"     
#define ADNGROUP      "adn-group33" 

#ifndef LED_BUILTIN

#endif

// Blink timings (ms)
const uint16_t SLOW_ON  = 300;
const uint16_t SLOW_OFF = 700;
const uint16_t FAST_ON  = 100;
const uint16_t FAST_OFF = 100;

const uint32_t CONNECT_TIMEOUT_MS = 10000;

static void blink(uint16_t on_ms, uint16_t off_ms) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(on_ms);
  digitalWrite(LED_BUILTIN, LOW);
  delay(off_ms);
}

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Booting...");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.setHostname(ADNGROUP);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < CONNECT_TIMEOUT_MS) {
    blink(SLOW_ON, SLOW_OFF);    // Trying to connect: slow blink
    Serial.print('.');
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);      // Connected: LED ON
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());       // -> WiFi.localIP()
  } else {
    Serial.println("Connect failed after 10 s. Fast blinking.");
    while (true) {
      blink(FAST_ON, FAST_OFF);           // Failed: fast blink forever
    }
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);      // Keep LED solid ON when connected
    delay(200);
  } else {
    blink(FAST_ON, FAST_OFF);             // If dropped later: fast blink
  }
}

