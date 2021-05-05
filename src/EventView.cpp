// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "EventView.h"

void EventItem::show() {
  canvas.drawString(item["summary"].as<char*>(), 0, ITEM_MARGIN);
  canvas.pushCanvas(x, y, UPDATE_MODE_GLR16);
}

void showEvents(int32_t x, int32_t y, DynamicJsonDocument doc) {
  JsonArray events = doc.as<JsonArray>();
  int i = 0;
  for(JsonVariant event : events) {
    EventItem eventView(x, y + (ListItem::ITEM_FONT_SIZE + 3 + ListItem::ITEM_MARGIN * 2) * i, event);
    eventView.show();
    i++;
  }
}
