#include "face.h"

namespace fb {

using namespace std;

/*++++++++++++++++++++++++++++++++++++++++
 * FaceBooklet methods
 ----------------------------------------*/

FaceBooklet::FaceBooklet() : db(Database())
{
  prompter = Prompter(&db);
}

FaceBooklet::~FaceBooklet() { }

void FaceBooklet::run() { }


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

} // fb