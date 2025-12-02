#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>
#include <string.h>

#define WIFI_SSID "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"
#define MQTT_BROKER "192.168.0.1"
#define MQTT_TOPIC "adn/group33/temp"
#define HOSTNAME "adn-group33"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqttClient.setServer(MQTT_BROKER, 1883);
  while (!mqttClient.connected()) mqttClient.connect(HOSTNAME, HOSTNAME, NULL);
  bme.begin(0x76);
}

void loop() {
  if (!mqttClient.connected())
    while (!mqttClient.connected()) mqttClient.connect(HOSTNAME, HOSTNAME, NULL);
  mqttClient.loop();
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 5000) {
    lastPublish = millis();
    float temp = bme.readTemperature();
    char payload[4];
    memcpy(payload, &temp, 4);
    mqttClient.publish(MQTT_TOPIC, (uint8_t*)payload, 4);
  }
}
