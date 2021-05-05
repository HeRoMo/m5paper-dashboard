// Copyright (c) 2021 HeRoMo
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _TODO_VIEW_H_
#define _TODO_VIEW_H_

#include "ListItem.h"

class TodoItem : public ListItem
{
  public:
    TodoItem(int32_t x, int32_t y, JsonVariant event): ListItem(x, y, event) {};
    void show();
};

void showTodos(int32_t x, int32_t y, DynamicJsonDocument doc);

#endif
