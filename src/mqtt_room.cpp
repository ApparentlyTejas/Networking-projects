#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>

#define WIFI_SSID     "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"
#define MQTT_BROKER   "192.168.0.1"
#define MQTT_TOPIC    "adn/group33/room"   
#define HOSTNAME      "adn-group33"

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
Adafruit_BME280 bme;

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMQTT() {
  mqtt.setServer(MQTT_BROKER, 1883);
  while (!mqtt.connected()) mqtt.connect(HOSTNAME, HOSTNAME, NULL);
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  connectMQTT();
  bme.begin(0x76);          
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  static unsigned long last = 0;
  if (millis() - last > 30000) {     
    last = millis();

    float t = bme.readTemperature(); 
    float h = bme.readHumidity();    
    float p = bme.readPressure();    

    Serial.print("T="); Serial.print(t);
    Serial.print(" H="); Serial.print(h);
    Serial.print(" P="); Serial.println(p);

    char payload[12];
    memcpy(payload,      &t, 4);
    memcpy(payload + 4,  &h, 4);
    memcpy(payload + 8,  &p, 4);

    mqtt.publish(MQTT_TOPIC, (uint8_t*)payload, 12);
  }
}
