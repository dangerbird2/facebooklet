#include "face.h"
#include <time.h>
#include <stdio.h>
#include <numeric>
#include <limits>

namespace fb {

using namespace std;

/*++++++++++++++++++++++++++++++++++++++++
 * FaceBooklet methods
 ----------------------------------------*/



FaceBooklet::FaceBooklet()
    :db(Database())
{
  active_profile = nullptr;
  prompter = Prompter(&db);
}

FaceBooklet::~FaceBooklet() { }




std::ostream &operator<<(std::ostream &os, const IFaceBookletNode &node)
{
  return os << node.describe();
}

bool operator==(IFaceBookletNode const &self, IFaceBookletNode const &rhs)
{
  return self.get_id() == rhs.get_id();
}

FaceBooklet::FaceBooklet(Database &&db)
    : db(std::move(db))
{
  prompter = Prompter(&db);
}

Database *FaceBooklet::get_db() { return &db; }


void FaceBooklet::run()
{
  cout << "Welcome to facebooklet!\n\n";
  running = true;
  while (running) {

    main_menu();

  }
}

void FaceBooklet::main_menu()
{
  string uname = active_profile?
                 active_profile->get_data().get_name():
                 "none";
  cout << "USER: " << uname << ",\n";
  cout << "Please choose an option";
  vector<string> choices = {"create a new profile",
                            "log into a profile",
                            "view profile",
                            "quit"};
  if (active_profile) {
    vector<string> user_choices = {"add a friend",
                                   "remove a friend",
                                   "make a post"};
    // merge the two vectors
    choices.insert(choices.end(), user_choices.begin(), user_choices.end());
  }

  auto res = prompter.prompt_choice(cin, choices);
  if (res < choices.size()) {
    cout << "you chose " << choices[res] << "\n";
    switch (static_cast<MenuOpt>(res)) {
      case (MenuOpt::createProfile): create_profile(); break;
      case (MenuOpt::login): login(); break;
      case (MenuOpt::viewProfile): view_profile(); break;
      case (MenuOpt::addFriend): add_friend(); break;
      case (MenuOpt::remFriend): rem_friend(); break;
      case (MenuOpt::quit): { quit(); break; }
      case (MenuOpt::post): { post(); break; }
    }
    cout << "\n\n";

  } else {
    cout << "please chose valid option\n";
  }
}


void FaceBooklet::set_running(bool running)
{
  this->running = running;
}

bool FaceBooklet::is_running() const
{
  return running;
}


void FaceBooklet::create_profile()
{
  active_profile = prompter.create_profile(cin);
}

void FaceBooklet::login()
{
  active_profile = prompter.prompt_username(cin);
}

void FaceBooklet::del_profile()
{

}

void FaceBooklet::view_profile()
{
  IFaceBookletNode *prof = nullptr;
  prof = prompter.prompt_username(cin);

  if (prof) {
    auto const &data = prof->get_data();
    cout << *prof << " created at " << data.get_time() << "\n";

    cout << "FRIENDS:\n";
    auto friends = prof->get_friend_ids();
    for(auto const &i: friends) {
      if (prof->has_friend(i)) {
        auto fr = prof->get_friend(i);
        cout << "\t" << *fr;
      }
    }

    for (auto const &i: data.get_posts()) {
      cout << "\tPOST: " << i.text << "\n\tposted at: " << i.time << "\n\n";
      cin.get();
    }
  }
}

void FaceBooklet::quit()
{
  cout << "goodbye!\n";
  running = false;
}

void FaceBooklet::add_friend()
{
  IFaceBookletNode *prof = nullptr;
  prof = prompter.prompt_username(cin);
  if (prof && active_profile) {
    active_profile->add_friend(prof);
    prof->add_friend(active_profile);
  }
}

void FaceBooklet::rem_friend()
{
  IFaceBookletNode *prof = nullptr;
  prof = prompter.prompt_username(cin);
  if (prof && active_profile) {
    prof->remove_friend(active_profile->get_id());
    active_profile->remove_friend(prof->get_id());
  }
}

void FaceBooklet::post()
{
  if (active_profile) {
    prompter.make_post(cin, active_profile);
  }
}


/*++++++++++++++++++++++++++++++++++++++++
 * Prompter methods
 ----------------------------------------*/

Profile *Prompter::create_profile(std::istream &in)
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
      std::cout << "\nplease enter a name" << std::endl;
    } else {
      std::cout << "\nyour name is " << name << std::endl;
      res = true;
    }
  }
  res = false;

  auto bday = Date(d, static_cast<Month>(m), y);
  auto profile = db->insert_profile(name, t, bday);
  return profile;
}

IFaceBookletNode * Prompter::prompt_username(std::istream &in)
{
  IFaceBookletNode *prof = nullptr;
  string uname;
  cout << "please enter your username\n->";
  in >> uname;


  vector<id_t> ids = db->ids_with_name(uname);
  if (ids.size() > 1) {
    cout << "we found more than one user with name " << uname
      << ".\nPlease select user by user ID\n";

    auto choice = prompt_choice(in, ids);

    prof = db->get_node(ids[choice]);


  } else if (ids.size() == 1) {
    prof = db->get_node(ids[0]);
  } else {
    cout << "sorry, could not find user with name " << uname << "\n";
  }

  return prof;
}

NodePost *Prompter::prompt_post(std::istream &in)
{
  return nullptr;
}


template <typename T>
size_t Prompter::prompt_choice(std::istream &in,
                               std::vector<T> const &choices)
{
  size_t choice = choices.size() + 1;

  cout << "pick an option:\n";
  for (auto i = 0; i < choices.size(); ++i) {
    cout << "\t(" << i << ") " << choices[i] << ",\n";
  }

  cout << "->";
  const int n = 5;


  for (int i = 0; i < n; ++i) {
    string buffer;
    in >> buffer;

    choice = strtoul(buffer.c_str(), NULL, 10);
    if (errno == ERANGE) {
      cout << "bad input: couldn't convert to number value " << buffer <<"\n";
    } else if (choice == 0 && buffer != "0") {
      cout << "invalid option:" << buffer << " , try again\n->";
      in.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }


  return choice;
}


void Prompter::make_post(std::istream &in, IFaceBookletNode *active_profile)
{
  if (!active_profile) {return;}
  string input;
  string post;
  cout << active_profile->get_data().get_name() << ", what do you have to say?\n->";

  in >> input;
  getline(in, post);

  post = input + post;

  cout << post << "\n\n";

  auto t = time(NULL);
  auto node_post = NodePost(post, t);

  active_profile->
      get_data().
      get_posts().
      push_back(node_post);

}


} // fb