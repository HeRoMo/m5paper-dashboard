#include <WiFi.h>
#include <M5EPD.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include "FS.h"
#include "SPIFFS.h"
#include "connect_wifi.h"

#define FONT_SIZE 32
#define MDNS_NAME "m5paper-dashboard"
// #define WIFI_SSID // define in platformio.ini
// #define WIFI_PASSWORD // define in platformio.ini
// #define MQTT_BROKER // define in platformio.ini

M5EPD_Canvas canvas(&M5.EPD);

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  Serial.print("Message arrived [" + String(topic) + "] ");
  String message = String((char*) payload);
  Serial.println(message);
  canvas.drawString(message, 45, 35);
  canvas.pushCanvas(0,0,UPDATE_MODE_GC16);
}

PubSubClient mqttClient(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("outTopic","hello world");
      // ... and resubscribe
      mqttClient.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void initMDNS(const char* hostname)
{
  Serial.print("mDNS server instancing.");
  while (!MDNS.begin(hostname)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("success!");
}

void setup()
{
  M5.begin();
  M5.EPD.SetRotation(0);
  M5.EPD.Clear(true);

  connectWifi(WIFI_SSID, WIFI_PASSWORD);
  initMDNS(MDNS_NAME);

  M5.RTC.begin();
  canvas.loadFont("/font.ttf", SD);
  canvas.createCanvas(960, 540);
  canvas.createRender(FONT_SIZE, 256);
  canvas.setTextSize(FONT_SIZE);

  IPAddress ip = MDNS.queryHost(MQTT_BROKER);
  Serial.print(MQTT_BROKER);
  Serial.println(" is " + ip.toString());
  mqttClient.setServer(ip, 1883);
  mqttClient.setCallback(callback);
}

void loop()
{
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
