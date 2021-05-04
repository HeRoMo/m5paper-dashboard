// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _TODO_VIEW_H_
#define _TODO_VIEW_H_

#include <ArduinoJson.h>
#include <M5EPD.h>

class TodoItem {
  private:
    int x;
    int y;
    JsonVariant event;
    M5EPD_Canvas canvas;

  public:
    TodoItem(int32_t x, int32_t y, JsonVariant event);
    ~TodoItem();
    void show();
};

void showTodos(int32_t x, int32_t y, DynamicJsonDocument doc);

#endif
