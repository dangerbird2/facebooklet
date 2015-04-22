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


/**
 * Steve Shea
 * @file
 * @brief declarations for the prompter and main Facebooklet class.
 * @details For this project, I have chosen to roughly emulate a model-view-controller
 * architecture as a way of separating concerns of the various classes. The IFacebookletNode,
 * Profile, Database, and NodeData classes make up the model by manipulating and storing data.
 * The Prompter class handles user input. It is given instructions from the Facebooklet instance,
 * and provides promts and parses input. Rather than using std::cin dirrectly, it takes a std::istream
 * object reference. This allows for easier testing, as you can pass in a stringstream object
 * to emulate user input (this can be seen in the test cases of test/engine_tests.c). Finally, The
 * Facebooklet class acts as the controller. It provides an interface between the model and the
 * user interactions handled by Prompter, such as adding users or posts. It also provides
 * the program's main loop method.
 */

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

  Profile *create_profile(std::istream &in);

  IFaceBookletNode * prompt_username(std::istream &in);

  NodePost *prompt_post(std::istream &in);


  void make_post(std::istream &in, IFaceBookletNode *active_profile);

  template <typename T>
  size_t prompt_choice(std::istream &in, std::vector<T> const &choices);

  Database *db;
};

/**
 * @brief enum class for options
 * available to main menu
 */
enum class MenuOpt {
  createProfile,
  login,
  viewProfile,
  quit,
  addFriend,
  remFriend,
  post
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

  bool is_running() const;
  void set_running(bool running);

  /*+++++++++++++++++++++++++++
   * app action controller funtions
   ----------------------------*/
  /**
   * @brief displays and prompts user the main menu
   */
  void main_menu();

  void create_profile();

  void login();
  void del_profile();
  void view_profile();
  void quit();
  void add_friend();
  void rem_friend();
  void post();



  Database *get_db();

private:
  Database db;

  Prompter prompter;
  bool running = true;

  IFaceBookletNode *active_profile;
};

} // fb

#endif // FACE_BOOKLET_H
