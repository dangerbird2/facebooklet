//
// Created by Steven on 4/18/15.
//

#include "Date.h"

namespace fb {

Date::Date(time_t day, Month month, time_t year) :
    day(day), month(month), year(year)
{
  if (day < 1) {this->day = 1;}

}

bool operator==(Date const &lhs, Date const &rhs)
{
  return
      lhs.day == rhs.day &&
      lhs.month == rhs.month &&
      lhs.year == rhs.year;
}

}
