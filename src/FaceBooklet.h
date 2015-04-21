/**
 * Steve Shea
 * 
 * @file
 * @brief defines main Facebooklet class
 */
#ifndef FACE_BOOKLET_H
#define FACE_BOOKLET_H

#include <iostream>
#include "FBProfile.h"
#include "Date.h"


namespace fb {

// predeclared database class
class Database;


/**
 * @brief template class for prompting user for data
 * @details Implemented as a template class for generic
 * i/o streams. Allows automated testing of prompter 
 * with string streams
 *
 */

class Prompter {
public:
  Prompter(Database *db = nullptr) : db(db) { }

  /**
   * @brief generates a new profile
   * 
   * @param db pointer to the database object
   * @return a pointer to the new profile, added
   * to the database
   */
  Profile *create_profile(std::istream &in)
  {
    if (!db) { return nullptr; }
    auto t = time(NULL);
    std::string name;
    int m = -1;
    int y = -1;
    int d = -1;
    bool res = false;

    const int n = 5;
    for (int i = 0; i < n && !res; ++i) {
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



    auto bday = Date(d, static_cast<Month>(m), y);
    auto profile = db->insert_profile(name, t, bday);
    return profile;
  }

  Database *db;
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
  FaceBooklet(Database &&db);

  /**
   * @brief copy constructor
   */
  FaceBooklet(FaceBooklet &book) = delete;
  virtual ~FaceBooklet();

  /**
   * @brief runs the program
   * @details [long description]
   */
  void run();

  Database *get_db();

private:
  Database db;
  Prompter prompter;

};

} // fb

#endif // FACE_BOOKLET_H
