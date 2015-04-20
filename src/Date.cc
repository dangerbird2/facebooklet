//
// Created by Steven on 4/18/15.
//

#include "Date.h"

fb::Date::Date(time_t day, fb::Month month, time_t year):
day(day), month(month), year(year)
{
  if (day < 1) {day = 1;}

}

