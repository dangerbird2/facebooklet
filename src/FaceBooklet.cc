#include "face.h"
#include <time.h>

namespace fb {

using namespace std;

/*++++++++++++++++++++++++++++++++++++++++
 * FaceBooklet methods
 ----------------------------------------*/

enum class MenuOpt {
  createProfile,
  login,
  delProfile,
  viewProfile,
  quit,
  addFriend,
  remFriend,
  post
};

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
  cout << "Please choose an option";
  vector<string> choices = {"create a new profile",
                            "log into a profile",
                            "delete a profile",
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
      case (MenuOpt::quit): {
        cout << "goodbye!\n";
        running = false;
        break;
      }
      case (MenuOpt::post): {
        prompter.make_post(cin, active_profile);
      }
      default: {
      }
    }


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

Profile *Prompter::prompt_username(std::istream &in)
{
  return nullptr;
}

NodePost *Prompter::prompt_post(std::istream &in)
{
  return nullptr;
}

Profile *Prompter::prompt_finduser(std::istream &in)
{
  return nullptr;
}

Profile *Prompter::prompt_userid(std::istream &in)
{
  return nullptr;
}

size_t Prompter::prompt_choice(std::istream &in,
                               std::vector<std::string> const &choices)
{
  size_t choice = choices.size() + 1;

  cout << "pick an option:\n";
  for (auto i = 0; i < choices.size(); ++i) {
    cout << "\t(" << i << ") " << choices[i] << ",\n";
  }

  cout << "->";
  const int n = 5;


  for (int i = 0; i < n; ++i) {
    in >> choice;
    if (choice < choices.size()) {
      break;
    } else {
      cout << "invalid option, try again\n->";
    }
  }

  return choice;
}


void Prompter::make_post(std::istream &in, Profile *active_profile)
{
  if (!active_profile) {return;}
  string post;
  cout << active_profile->get_data().get_name() << ", what do you have to say?\n->";
  in >> post;
  auto t = time(NULL);
  auto node_post = NodePost(post, t);

  active_profile->
      get_data().
      get_posts().
      push_back(node_post);

}

} // fb