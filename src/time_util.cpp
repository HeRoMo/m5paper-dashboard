// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "time_util.h"

time_t t;
struct tm *tm;

static const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

void drawDateTime(char* timeStr) {
  int width = 475;
  int height = 40;
  int color = 15;
  int ofsetY = (60 - height) / 2;
  int fontSize = height;
  M5EPD_Canvas canvas(&M5.EPD);
  canvas.loadFont("/font.ttf", SD);
  canvas.createRender(fontSize, 256);

  canvas.createCanvas(width, height);
  canvas.setTextSize(fontSize);
  canvas.setTextColor(0, color);
  canvas.drawString(timeStr, 0, 0);
  canvas.pushCanvas(20, ofsetY, UPDATE_MODE_A2);
  canvas.deleteCanvas();
}

void setupRTCTime() {
  t = time(NULL);
  tm = localtime(&t);

  RTCtime.hour = tm->tm_hour;
  RTCtime.min = tm->tm_min;
  RTCtime.sec = tm->tm_sec;
  M5.RTC.setTime(&RTCtime);

  RTCDate.year = tm->tm_year + 1900;
  RTCDate.mon = tm->tm_mon + 1;
  RTCDate.day = tm->tm_mday;
  M5.RTC.setDate(&RTCDate);
}

void showDateTime(char* lastTime) {
  char currentTime[23];

  sprintf(currentTime, "%d/%02d/%02d (%s) %02d:%02d",
          RTCDate.year, RTCDate.mon, RTCDate.day,
          wd[RTCDate.week],
          RTCtime.hour, RTCtime.min);
  if (strcmp(lastTime, currentTime) != 0) {
    Serial.println(currentTime);
    drawDateTime(currentTime);
    strcpy(lastTime, currentTime);
  }
}
