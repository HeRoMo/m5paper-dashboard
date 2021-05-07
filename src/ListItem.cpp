// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "ListItem.h"

ListItem::ListItem(int32_t x, int32_t y, JsonVariant item): x(x), y(y), item(item), canvas(&M5.EPD) {
  canvas.loadFont("/font.ttf", SD);
  canvas.createRender(ITEM_FONT_SIZE, 256);
  canvas.createCanvas(960, ITEM_FONT_SIZE + ITEM_MARGIN * 2);
  canvas.setTextSize(ITEM_FONT_SIZE);
};

ListItem::~ListItem() {
  canvas.deleteCanvas();
}

void ListItem::blank() {
  canvas.fillCanvas(0);
  canvas.pushCanvas(x, y, UPDATE_MODE_GLR16);
}
