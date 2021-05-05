// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "TodoView.h"

void TodoItem::show() {
  canvas.drawString(item["content"].as<char*>(), 0, ITEM_MARGIN);
  canvas.pushCanvas(x, y, UPDATE_MODE_GLR16);
}

void showTodos(int32_t x, int32_t y, DynamicJsonDocument doc) {
  JsonArray todos = doc["todoList"].as<JsonArray>();
  int i = 0;
  for(JsonVariant todo : todos) {
    TodoItem todoView(x, y + (ListItem::ITEM_FONT_SIZE + 3 + ListItem::ITEM_MARGIN * 2) * i, todo);
    todoView.show();
    i++;
  }
}
