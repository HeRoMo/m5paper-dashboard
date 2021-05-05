// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _EVENT_VIEW_H_
#define _EVENT_VIEW_H_

#include "ListItem.h"

class EventItem : public ListItem
{
  public:
    EventItem(int32_t x, int32_t y, JsonVariant event): ListItem(x, y, event) {};
    void show();
};

void showEvents(int32_t x, int32_t y, DynamicJsonDocument doc);

#endif
