// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "EventView.h"

#define EVENT_FONT_SIZE 32

EventItem::EventItem(int32_t x, int32_t y, JsonVariant event): x(x), y(y), event(event), canvas(&M5.EPD) {
  canvas.loadFont("/font.ttf", SD);
  canvas.createCanvas(960, EVENT_FONT_SIZE + 10);
  canvas.createRender(EVENT_FONT_SIZE, 256);
  canvas.setTextSize(EVENT_FONT_SIZE);
};

EventItem::~EventItem() {
  canvas.deleteCanvas();
}

void EventItem::show() {
  canvas.drawString(event["summary"].as<char*>(), 0, 0);
  canvas.pushCanvas(x, y, UPDATE_MODE_GLR16);
}

void showEvents(int32_t x, int32_t y, DynamicJsonDocument doc) {
  JsonArray events = doc.as<JsonArray>();
  int i = 0;
  for(JsonVariant event : events) {
    EventItem eventView(x, y + (EVENT_FONT_SIZE + 3) * i, event);
    eventView.show();
    i++;
  }
}
