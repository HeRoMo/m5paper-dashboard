// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "headers.h"

void drawHeader(int y, int height, int color, char* title) {
  int margin = 5;
  int fontSize = height - margin * 2;
  M5EPD_Canvas canvas(&M5.EPD);
  canvas.loadFont("/font.ttf", SD);
  canvas.createRender(fontSize, 256);
  canvas.createCanvas(960, height);
  canvas.fillCanvas(color);
  canvas.setTextSize(fontSize);
  canvas.setTextColor(0, color);
  canvas.drawString(title, 20, margin);
  canvas.pushCanvas(0, y, UPDATE_MODE_GLR16);
  canvas.deleteCanvas();
}
