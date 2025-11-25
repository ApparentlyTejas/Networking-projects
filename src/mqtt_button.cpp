#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncMqttClient.h>
#include <avdweb_Switch.h>

#define WIFI_SSID "ADN-IOT"
#define WIFI_PASS "WBNuyawB2a"

#define MQTT_HOST IPAddress(192,168,0,255)
#define MQTT_PORT 1883

#define BUTTON_PIN 17
Switch button = Switch(BUTTON_PIN);

AsyncMqttClient mqttClient;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.connect();
  while (!mqttClient.connected()) {
    delay(200);
  }
}

void loop() {
  button.poll();

  if (button.pushed()) {
    mqttClient.publish("cmnd/adn37/POWER", 1, false, "TOGGLE");
  }
}
