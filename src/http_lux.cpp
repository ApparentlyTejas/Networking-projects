#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_TSL2561_U.h>

// WiFi credentials
#define WIFI_SSID     "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"

// Smart socket IP
const char* SOCKET_IP = "192.168.0.51";

// Light sensor
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// Hysteresis thresholds 
const int LUX_ON_THRESHOLD  = 50;    
const int LUX_OFF_THRESHOLD = 150;    

// Track current socket state
bool socketIsOn = false;   

// Send ON/OFF HTTP command
void sendSocketCommand(bool turnOn) {
  HTTPClient http;
  String url = "http://";
  url += SOCKET_IP;
  url += "/cm?cmnd=Power%20";
  url += (turnOn ? "On" : "Off");

  Serial.print("Request: ");
  Serial.println(url);

  http.begin(url);
  int code = http.GET();

  Serial.print("HTTP response: ");
  Serial.println(code);

  if (code > 0) {
    Serial.println(http.getString());
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // WiFi 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Sensor setup
  if (!tsl.begin()) {
    Serial.println("TSL2561 not found!");
    while (1);
  }
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);

  Serial.println("Socket assumed OFF at startup.");
}

void loop() {
  // Read light sensor 
  sensors_event_t event;
  tsl.getEvent(&event);

  float lux = event.light;

  Serial.print("Lux: ");
  Serial.println(lux);

  // Decision logic with hysteresis
  if (!socketIsOn && lux < LUX_ON_THRESHOLD) {
    Serial.println("Dark → Turning socket ON");
    sendSocketCommand(true);
    socketIsOn = true;
  }
  else if (socketIsOn && lux > LUX_OFF_THRESHOLD) {
    Serial.println("Bright → Turning socket OFF");
    sendSocketCommand(false);
    socketIsOn = false;
  }

  delay(500);
}
