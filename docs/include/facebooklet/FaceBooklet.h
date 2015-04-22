/**
 * Steve Shea
 * 
 * @file
 * @brief defines main Facebooklet class
 */
#ifndef FACE_BOOKLET_H
#define FACE_BOOKLET_H


#include "Database.h"
#include "FBProfile.h"
#include <memory>
#include <iostream>
#include <string>

namespace fb {

// predeclared database class
class Database;


/**
 * @brief template class for prompting user for data
 * @details Implemented as a template class for generic
 * i/o streams. Allows automated testing of prompter 
 * with string streams
 * 
 * @tparam ISTREAM_T=std::istream an input stream STL
 * type
 */
template<typename ISTREAM_T=std::istream>
class Prompter {
public:
  Prompter(ISTREAM_T &in) : in(in) { }

  /**
   * @brief generates a new profile
   * 
   * @param db pointer to the database object
   * @return a pointer to the new profile, added
   * to the database
   */
  Profile *create_profile(Database *db)
  {
    auto t = time(NULL);
    std::string name;
    int m = -1;
    int y = -1;
    int d = -1;
    bool res = false;
    while (!res) {
      std::cout << "what is your name?->";
      in >> name;
      if (name == "") {
        std::cout << "please enter a name" << std::endl;
      } else {
        std::cout << "your name is" << name << std::endl;
        res = true;
      }
    }
    res = false;

    while (!res) {

      res = true;
    }


    auto bday = Date(d, static_cast<Month>(m), y);
    auto profile = db->insert_profile(name, t, bday);
    return profile;
  }

  ISTREAM_T &in;
};


/**
 * @brief main function for FaceBooklet program.
 * @details functions essentially as a Controller object
 * in a MVC application.
 */
class FaceBooklet {
public:
  /**
   * @brief default constructor
   */
  FaceBooklet();

  /**
   * @brief constructor
   * 
   * @param db database object (copied to the db field)
   * @param prompter promper object for user input
   */
  FaceBooklet(Database const &db, Prompter<std::istream> const &prompter);

  /**
   * @brief copy constructor
   */
  FaceBooklet(FaceBooklet &book);

  virtual ~FaceBooklet();

  /**
   * @brief runs the program
   * @details [long description]
   */
  void run();

  Prompter<std::istream> prompter;
  Database db;
};


} // fb

#endif // FACE_BOOKLET_H
