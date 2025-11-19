#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID     "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"


const char* SOCKET_IP = "192.168.0.51";  

String makeToggleUrl(const char* ip) {
  String url = "http://";
  url += ip;
  url += "/cm?cmnd=Power%20TOGGLE";
  return url;
}

const uint32_t TOGGLE_PERIOD_MS = 2000;   
unsigned long lastToggle = 0;

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Booting...");

  WiFi.mode(WIFI_STA);                             
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);            
  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {          
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());                  

 
  delay(200);
}

void loop() {
  
  if (millis() - lastToggle >= TOGGLE_PERIOD_MS) {
    lastToggle = millis();

    if (WiFi.status() == WL_CONNECTED) {           
      String url = makeToggleUrl(SOCKET_IP);

      HTTPClient http;                              
     
      http.begin(url);                               
      int httpCode = http.GET();                     

      if (httpCode > 0) {
        Serial.print("HTTP GET code: ");
        Serial.println(httpCode);                    
        String payload = http.getString();           
        Serial.print("Response: ");
        Serial.println(payload);                     
      } else {
        Serial.print("HTTP GET failed, error: ");
        Serial.println(httpCode);                    
      }

      http.end();                                  
    } else {
      Serial.println("WiFi disconnected, skipping toggle.");
    }
  }


  delay(10);
}
