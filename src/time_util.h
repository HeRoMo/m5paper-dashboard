// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#ifndef _TIME_UTIL_H_
#define _TIME_UTIL_H_

#include <M5EPD.h>

extern rtc_time_t RTCtime;
extern rtc_date_t RTCDate;

void setupRTCTime();
void showDateTime(char* lastTime);
#endif
