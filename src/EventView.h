// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _EVENT_VIEW_H_
#define _EVENT_VIEW_H_

#include <ArduinoJson.h>
#include <M5EPD.h>

class EventItem {
  private:
    int x;
    int y;
    JsonVariant event;
    M5EPD_Canvas canvas;

  public:
    EventItem(int32_t x, int32_t y, JsonVariant event);
    ~EventItem();
    void show();
};

void showEvents(int32_t x, int32_t y, DynamicJsonDocument doc);

#endif
