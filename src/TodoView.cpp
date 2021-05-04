// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "TodoView.h"

#define EVENT_FONT_SIZE 32

TodoItem::TodoItem(int32_t x, int32_t y, JsonVariant event): x(x), y(y), event(event), canvas(&M5.EPD) {
  canvas.loadFont("/font.ttf", SD);
  canvas.createCanvas(960, EVENT_FONT_SIZE + 10);
  canvas.createRender(EVENT_FONT_SIZE, 256);
  canvas.setTextSize(EVENT_FONT_SIZE);
};

TodoItem::~TodoItem() {
  canvas.deleteCanvas();
}

void TodoItem::show() {
  canvas.drawString(event["content"].as<char*>(), 0, 0);
  canvas.pushCanvas(x, y, UPDATE_MODE_GLR16);
}

void showTodos(int32_t x, int32_t y, DynamicJsonDocument doc) {
  JsonArray todos = doc["todoList"].as<JsonArray>();
  int i = 0;
  for(JsonVariant todo : todos) {
    TodoItem todoView(x, y + (EVENT_FONT_SIZE + 3) * i, todo);
    todoView.show();
    i++;
  }
}
