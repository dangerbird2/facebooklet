//
// Created by Steven on 4/18/15.
//

#ifndef FACEBOOKLET_DATETIME_H
#define FACEBOOKLET_DATETIME_H

#include <time.h>

namespace fb {


enum class Month {
  Jan = 1,
  Feb,
  Mar,
  Apr,
  May,
  Jun,
  Jul,
  Aug,
  Sep,
  Oct,
  Nov,
  Dec
};

struct Date {
public:
  Date(time_t day=1, Month month=Month::Jan , time_t=1970);

  time_t day;
  Month month;
  time_t year;
};



}


#endif //FACEBOOKLET_DATETIME_H
