#include <WiFi.h>
#include <M5EPD.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"
#include "connect_wifi.h"
#include "init_mdns.h"
#include "EventView.h"
#include "TodoView.h"
#include "headers.h"
#include "time_util.h"

#define FONT_SIZE 32
#define MDNS_NAME "m5paper-dashboard"
#define MQTT_MAX_PACKET_SIZE 2048
// #define WIFI_SSID // define in platformio.ini
// #define WIFI_PASSWORD // define in platformio.ini
// #define MQTT_BROKER // define in platformio.ini

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  Serial.print("Message arrived [" + String(topic) + "] ");
  String message = String((char*) payload);
  Serial.println(message);
  DynamicJsonDocument doc(MQTT_MAX_PACKET_SIZE);

  deserializeJson(doc, message);
  serializeJsonPretty(doc, Serial);

  if (strcmp(topic,"calendar")==0) {
    showEvents(0, 120, doc);
  } else if (strcmp(topic,"todo")==0) {
    showTodos(20, 320, doc);
  }
}

PubSubClient mqttClient(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(MDNS_NAME)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("log", "Dashboard is connected.");
      // ... and resubscribe
      mqttClient.subscribe("calendar", 1);
      mqttClient.subscribe("todo", 1);
      mqttClient.subscribe("inTopic", 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

static const int JST = 3600 * 9;

void setup()
{
  M5.begin();
  M5.RTC.begin();
  M5.EPD.SetRotation(0);
  M5.EPD.Clear(true);

  drawHeader(0, 60, 15, "My Dashboard");
  drawHeader(65, 50, 10, "Event List");
  drawHeader(270, 50, 10, "Todo List");

  connectWifi(WIFI_SSID, WIFI_PASSWORD);
  initMDNS(MDNS_NAME);

  IPAddress ip = MDNS.queryHost(MQTT_BROKER);
  Serial.print(MQTT_BROKER);
  Serial.println(" is " + ip.toString());
  mqttClient.setServer(ip, 1883);
  mqttClient.setBufferSize(MQTT_MAX_PACKET_SIZE);
  mqttClient.setCallback(callback);

  configTime( JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
  delay(2000);
  setupRTCTime();
}

RTC_SLOW_ATTR bool ntpDataFlag = false;
rtc_time_t RTCtime;
rtc_date_t RTCDate;
char lastTime[23] = "0000/00/00 (000) 00:00";

void loop()
{
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  outputTimtToSerial(lastTime);

  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
