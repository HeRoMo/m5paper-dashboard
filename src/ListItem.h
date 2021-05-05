// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _LIST_ITEM_H_
#define _LIST_ITEM_H_

#include <ArduinoJson.h>
#include <M5EPD.h>

class ListItem {
  protected:
    int x;
    int y;
    JsonVariant item;
    M5EPD_Canvas canvas;

  public:
    static constexpr int ITEM_FONT_SIZE = 32;
    static constexpr int ITEM_MARGIN = 5;
    ListItem(int32_t x, int32_t y, JsonVariant item);
    ~ListItem();
    void blank();
    virtual void show() = 0;
};

#endif
