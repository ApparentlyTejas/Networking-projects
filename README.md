Networking Projects
Collection of small ESP32 networking exercises built with PlatformIO, focusing on Wi‑Fi, HTTP, and MQTT.

Projects
1. display_ip.cpp

Reads the ESP32’s assigned IP address after joining a Wi‑Fi network and prints it over the serial port.
Useful as a first sanity check that Wi‑Fi credentials, board, and PlatformIO setup are correct.

2. wifi_blink.cpp

Connects the ESP32 to Wi‑Fi and uses the onboard LED to indicate connection status (e.g. blinking while connecting, steady when connected).
Demonstrates basic Wi‑Fi state handling and non‑blocking LED signaling.

3. wifi_toggle.cpp

Connects to Wi‑Fi and toggles an attached light/socket by talking to an existing HTTP or MQTT API (depending on your implementation).
Focuses on triggering remote actions over the network.

4. http_lux.cpp

Reads a light sensor (lux value) and sends the measurements via HTTP to a server or REST endpoint.
Shows how to build and send HTTP requests from the ESP32 and how to integrate simple sensor inputs.

5. mqtt_temp.cpp

Reads a temperature (or temperature + humidity) sensor and publishes the values to an MQTT broker under a configured topic.
Introduces MQTT publish semantics, topics, QoS levels, and payload formatting.

6. mqtt_button.cpp

Connects to Wi‑Fi and an MQTT broker, monitors a hardware pushbutton, and sends a TOGGLE (or ON/OFF) command to a smart plug / Sonoff / Tasmota‑style device topic such as cmnd/sonoff_05/POWER.
Implements the classic IoT pattern of local input → MQTT message → remote actuator.

Requirements
ESP32 development board

USB cable and serial monitor

PlatformIO (VS Code extension or standalone)

A 2.4 GHz Wi‑Fi network

For MQTT examples:

MQTT broker (e.g. mosquitto or a lab broker such as 192.168.0.1:1883)​

Optional: tools like mosquitto_sub / mosquitto_pub to debug topics​

Libraries
Most sketches use a subset of these libraries:

Core

WiFi.h (ESP32 Wi‑Fi)

Asynchronous MQTT

AsyncTCP.h

AsyncMqttClient.h (marvinroger/AsyncMqttClient)​

Button handling

avdweb_Switch.h (Dalen switch library, often version 1.2.1 for lab exercises)

Sensors / extras

Depending on your sensors (e.g. lux/temperature), add the relevant sensor library via PlatformIO Library Manager.

Check each .cpp file’s #include list to see which of these are actually used.

Getting Started (PlatformIO)
Install VS Code
Download and install Visual Studio Code from the official website.

Install PlatformIO

Open VS Code.

Go to Extensions → search for “PlatformIO IDE” → install.​

Clone the repository

bash
git clone https://github.com/ApparentlyTejas/Networking-projects.git
cd Networking-projects
Open in PlatformIO

In VS Code: File → Open Folder… and select the Networking-projects folder.

PlatformIO will detect platformio.ini.

Select the example to build

Ensure the src folder contains the sketch you want to run (e.g. mqtt_button.cpp as src/main.cpp), or adjust your platformio.ini / file names accordingly.

Configure Wi‑Fi and broker

In the chosen .cpp file, edit:

WIFI_SSID, WIFI_PASS

MQTT broker IP/port and topics (e.g. cmnd/sonoff_05/POWER).

Build and upload

In the PlatformIO toolbar:

Click Build (checkmark) to compile.

Click Upload (right arrow) to flash the ESP32.

Open Serial Monitor to see logs and debug prints.

Running the MQTT examples
Use mosquitto_sub to watch messages while testing:

bash
mosquitto_sub -h 192.168.0.1 -t '#' -v
For mqtt_temp.cpp, subscribe to the temperature topic you configured.

For mqtt_button.cpp, subscribe to stat/<device-id>/# and press the button to see POWER toggling.

Repository Structure
src/

display_ip.cpp

wifi_blink.cpp

wifi_toggle.cpp

http_lux.cpp

mqtt_temp.cpp

mqtt_button.cpp

platformio.ini
PlatformIO environment configuration (board type, framework, library deps, etc.).