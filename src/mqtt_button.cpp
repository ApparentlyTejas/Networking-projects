#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncMqttClient.h>
#include <avdweb_Switch.h>

#define LED_PIN 2
#define WIFI_SSID "ADN-IOT"
#define WIFI_PASS "WBNuyawB2a"

#define MQTT_HOST IPAddress(192,168,0,01)
#define MQTT_PORT 1883

#define BUTTON_PIN 17
Switch button = Switch(BUTTON_PIN);

AsyncMqttClient mqttClient;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
  digitalWrite(LED_PIN , HIGH);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.connect();
  while (!mqttClient.connected()) {
    delay(200);
  }
}

void loop() {
  button.poll();

  if (button.pushed()) {
    serial.printlm("button pressed");
    mqttClient.publish("cmnd/sonoff05/POWER", 1, false, "TOGGLE");
  }
}
