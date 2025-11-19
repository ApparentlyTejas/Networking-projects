#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// WiFi credentials
#define WIFI_SSID     "ADN-IOT"
#define WIFI_PASSWORD "WBNuyawB2a"

// OLED
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(100);

  // --- OLED SETUP ---
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting...");
  display.display();

  // --- WIFI CONNECT ---
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  // --- SHOW IP ---
  String ip = WiFi.localIP().toString();

  Serial.print("IP address: ");
  Serial.println(ip);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("WiFi Connected");
  display.print("IP: ");
  display.println(ip);
  display.display();
}

void loop() {
  // nothing needed
}
