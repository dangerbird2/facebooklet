/**
 * Created by Steven on 4/18/15.
 * @file
 * @brief Date structure type
 */

#ifndef FACEBOOKLET_DATETIME_H
#define FACEBOOKLET_DATETIME_H

#include <time.h>

namespace fb {

/**
 * @brief enum class for Month values
 * @details begins with January (value 1)
 * 
 */
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

/**
 * @brief Date data structure.
 * @details Simple record type. Should
 * be used as a value type, rather than an
 * abstract object
 * 
 * @param day Must be value greater than one TODO:
 * limit date parameter to valid days in relavent month
 * @param month month value
 * @param year year
 */
struct Date {
public:
  Date(time_t day=1, Month month=Month::Jan, time_t year=1970);

  time_t day;
  Month month;
  time_t year;

  friend bool operator==(Date const &lhs, Date const &rhs);
};

bool operator==(Date const &lhs, Date const &rhs);


}


#endif //FACEBOOKLET_DATETIME_H
