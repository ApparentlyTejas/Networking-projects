#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

HardwareSerial gpsSerial(1);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
  delay(1000);
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() % 1000 == 0) {  // print about once per second
    double lat  = gps.location.lat();
    double lng  = gps.location.lng();
    double alt  = gps.altitude.meters();
    uint32_t hd = gps.hdop.value();
    uint32_t sats   = gps.satellites.value();
    uint32_t age    = gps.location.age();
    uint32_t failed = gps.failedChecksum();
    uint32_t chars  = gps.charsProcessed();

    Serial.print("lat="); Serial.print(lat, 6);
    Serial.print(" lon="); Serial.print(lng, 6);
    Serial.print(" alt="); Serial.print(alt);
    Serial.print(" hdop="); Serial.print(hd);
    Serial.print(" sats="); Serial.print(sats);
    Serial.print(" age="); Serial.print(age);
    Serial.print(" failed="); Serial.print(failed);
    Serial.print(" chars="); Serial.println(chars);
    delay(5);  // avoid double-print in same ms
  }
}
