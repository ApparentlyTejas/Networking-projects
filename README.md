
# Networking Projects

This repository contains a collection of small ESP32 networking exercises, developed with PlatformIO. The projects focus on exploring Wi‑Fi connectivity, sending HTTP requests, and communicating via MQTT.

## Projects

1. **display_ip.cpp**  
   Retrieves the ESP32’s assigned IP address after connecting to Wi‑Fi and outputs it to the serial port.  
   This is a handy first step to verify Wi‑Fi credentials and board setup.

2. **wifi_blink.cpp**  
   Connects the ESP32 to Wi‑Fi and uses the onboard LED to visually indicate connection status (e.g., blinking while connecting and steady on success).  
   Demonstrates basic asynchronous Wi‑Fi state monitoring and LED control.

3. **wifi_toggle.cpp**  
   Connects to Wi‑Fi and toggles a connected light/socket through HTTP or MQTT, depending on your setup.  
   This example shows how to remotely control devices over a network.

4. **http_lux.cpp**  
   Reads data from a light sensor (lux values) and sends it via HTTP to a server or REST endpoint.  
   Illustrates building and sending HTTP requests and integrating sensor input.

5. **mqtt_temp.cpp**  
   Reads temperature (and optionally humidity) sensor data and publishes it to an MQTT broker under a configurable topic.  
   Teaches MQTT publishing, topic structure, QoS settings, and payload formatting.

6. **mqtt_button.cpp**  
   Connects to Wi‑Fi and an MQTT broker, monitors a hardware pushbutton, and sends a TOGGLE (or ON/OFF) command to smart plugs such as Sonoff or Tasmota devices using topics like `cmnd/sonoff_05/POWER`.  
   Implements a classic IoT pattern: local sensor/input → MQTT message → remote actuator.

7. **lorawan.cpp (LoRaWAN GPS)**
   Connects an ESP32 + LoRaWAN shield to a LoRaWAN network, encodes GPS coordinates into an 11‑byte payload, and sends them in uplinks.
   Used together with a payload decoder and TTN Mapper to map gateway coverage and range.

8. **airtime_calc.md (LoRa airtime & duty cycle)**
   Contains the hand‑calculated LoRa airtime results (SF12, 125 kHz, 10‑byte uplink), duty‑cycle based message limits per day, and effective payload data rate.
   Summarizes theoretical trade‑offs between SF, bandwidth, coding rate, airtime, and fair‑use on LoRaWAN.

9. **printInfo.py (JSON & Python)**
   Simple Python 3 script that sends an HTTP request to the PyPI JSON API (https://pypi.org/pypi/sampleproject/json), parses the JSON response, and prints all entries with the       label filename using loops.
   Demonstrates basic use of urllib / json in Python and navigating nested JSON structures.

## Requirements

- ESP32 development board  
- USB cable and serial monitor (PlatformIO integrated)  
- PlatformIO IDE (VS Code extension or standalone)  
- A 2.4 GHz Wi‑Fi network  
- For MQTT projects:  
  - MQTT broker (e.g., mosquitto or the lab broker at 192.168.0.1:1883)  
  - Optional tools like `mosquitto_sub` and `mosquitto_pub` for debugging MQTT topics

## Libraries Used

The projects use a subset of these libraries depending on the sketch:

- **Core**  
  - `WiFi.h` (ESP32 Wi‑Fi support)

- **Asynchronous MQTT**  
  - `AsyncTCP.h`  
  - `AsyncMqttClient.h` (marvinroger/AsyncMqttClient)

- **Button handling**  
  - `avdweb_Switch.h` (the Dalen Switch library, often version 1.2.1 for stable debouncing)

- **Sensor extras**  
  - Depending on the sensor (light, temperature etc.), add the relevant sensor libraries via PlatformIO's Library Manager.

_Always check the includes at the top of each `.cpp` to see which libraries are required._

## Getting Started with PlatformIO

### 1. Install VS Code  
Download and install [Visual Studio Code](https://code.visualstudio.com/).

### 2. Install PlatformIO IDE Extension  
Open VS Code → Extensions → Search for “PlatformIO IDE” → Install.

### 3. Clone this repository  
git clone https://github.com/ApparentlyTejas/Networking-projects.git
cd Networking-projects

text

### 4. Open the folder in VS Code  
`File → Open Folder…` → select `Networking-projects`.

### 5. Select the sketch to build  
- Copy your chosen `.cpp` file to `src/main.cpp` or update your `platformio.ini` accordingly.

### 6. Configure credentials and settings  
Edit the selected `.cpp` files to update these defines:
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASS "your_wifi_password"
#define MQTT_HOST IPAddress(192,168,0,1) // your broker IP

text

Set MQTT topics as needed (e.g., `cmnd/sonoff_05/POWER`).

### 7. Build and upload  
Use PlatformIO toolbar:  
- Click Build (checkmark) to compile  
- Click Upload (right arrow) to flash to your ESP32  
- Open Serial Monitor to view debug output

## Running MQTT Example Debugging

Use these handy terminal commands with your broker:

Subscribe to all topics and watch output
mosquitto_sub -h 192.168.0.1 -t '#' -v

Subscribe to your device’s status updates (replace sonoff_05 with your device ID)
mosquitto_sub -h 192.168.0.1 -t 'stat/sonoff_05/#' -v

Manually toggle device power
mosquitto_pub -h 192.168.0.1 -t "cmnd/sonoff_05/POWER" -m "TOGGLE"

text

## Repository Layout

src/
├── display_ip.cpp
├── wifi_blink.cpp
├── wifi_toggle.cpp
├── http_lux.cpp
├── mqtt_temp.cpp
├── mqtt_button.cpp
├── lorawan.cpp
├── airtime_calc.md
├── printInfo.py

platformio.ini
README.md

text

---  
If you want to expand the repo or add new sketches, follow same style and PlatformIO conventions.

Happy coding!  
— Tejas  
