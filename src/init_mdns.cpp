// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "init_mdns.h"

void initMDNS(const char* hostname)
{
  Serial.print("mDNS server instancing.");
  while (!MDNS.begin(hostname)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("success!");
}
