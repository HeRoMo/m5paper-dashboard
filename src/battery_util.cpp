// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "battery_util.h"

void drawBattery(char* battery) {
  int width = 80;
  int height = 30;
  int color = 15;
  int fontSize = height;
  M5EPD_Canvas canvas(&M5.EPD);
  canvas.loadFont("/font.ttf", SD);
  canvas.createRender(fontSize, 256);

  canvas.createCanvas(width, height);
  canvas.setTextSize(fontSize);
  canvas.setTextColor(0, color);
  canvas.drawString(battery, 0, 0);
  canvas.pushCanvas(960 - width - 20, 25, UPDATE_MODE_A2);
  canvas.deleteCanvas();
}

void showBattery(char* lastBattery) {
  uint32_t vol = M5.getBatteryVoltage();
  if(vol < 3300) {
    vol = 3300;
  } else if(vol > 4350) {
    vol = 4350;
  }
  float battery = (float)(vol - 3300) / (float)(4350 - 3300);
  if(battery <= 0.01) {
      battery = 0.01;
  } else if(battery > 1) {
    battery = 1;
  }

  char currentBattery[5];
  sprintf(currentBattery, "%4d%%", (int)(battery * 100));
  if (strcmp(lastBattery, currentBattery) != 0) {
    Serial.printf("BATTERY VOL: %s\n", currentBattery);
    drawBattery(currentBattery);
    strcpy(lastBattery, currentBattery);
  }
}
