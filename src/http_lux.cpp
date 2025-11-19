#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// WiFi credentials
#define WIFI_SSID     "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"

// Smart socket IP
const char* SOCKET_IP = "192.168.0.51";  

// Lux thresholds
const float LUX_ON  = 100.0;  // turn socket ON if lux < 100
const float LUX_OFF = 300.0;  // turn socket OFF if lux > 300

// TSL2561 sensor setup
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// Current socket state
bool socketOn = false;

// Build HTTP URL to switch socket ON or OFF
String makeSwitchUrl(const char* ip, bool on) {
  String url = "http://";
  url += ip;
  url += "/cm?cmnd=Power%20";
  url += (on ? "ON" : "OFF");
  return url;
}

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Booting...");

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  // Initialize TSL2561
  if (!tsl.begin()) {
    Serial.println("TSL2561 not found!");
    while (1);
  }
  tsl.enableAutoRange(true);                     // auto gain
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);  // fast measurement
  Serial.println("TSL2561 initialized.");
}

void loop() {
  sensors_event_t event;
  tsl.getEvent(&event);

  if (event.light) {
    Serial.print("Lux: ");
    Serial.println(event.light);

    bool newState = socketOn;  // default: no change

    // Hysteresis logic
    if (socketOn && event.light > LUX_OFF) {
      newState = false; // turn OFF
    } else if (!socketOn && event.light < LUX_ON) {
      newState = true;  // turn ON
    }

    // Only send HTTP request if state changed
    if (newState != socketOn) {
      socketOn = newState;
      String url = makeSwitchUrl(SOCKET_IP, socketOn);
      Serial.print("Sending request: ");
      Serial.println(url);

      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode > 0) {
          Serial.print("HTTP code: "); Serial.println(httpCode);
          String payload = http.getString();
          Serial.println("Response: " + payload);
        } else {
          Serial.println("HTTP request failed!");
        }
        http.end();
      } else {
        Serial.println("WiFi disconnected, cannot switch socket.");
      }
    }
  } else {
    Serial.println("Sensor error");
  }

  delay(1000); // read sensor every 1 second
}
