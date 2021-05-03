// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "connect_wifi.h"

WiFiClient wifiClient;

void connectWifi(const char* ssid, const char* password)
{
  WiFi.begin(ssid, password);
  Serial.print("WiFi connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
  }
  Serial.println("success!");
}
