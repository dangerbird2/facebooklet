#include <facebooklet/face.h>
#include <sstream>

namespace fb {

using namespace std;

Profile::Profile(Database *db, std::string const &name)
    : db(db), profile_name(name), id(0) { }

const id_t Profile::get_id() const { return id; }

const std::string Profile::describe() const
{
  auto buff = stringstream();
  buff << "Profile:" << profile_name << " id:" << id;
  return buff.str();
}

IFaceBookletNode const *Profile::get_friend(id_t id) const { return nullptr; }

IFaceBookletNode *Profile::get_friend(id_t id) { return nullptr; }

void Profile::add_friend(IFaceBookletNode &fr) { }

void Profile::remove_friend(id_t id) { }

void Profile::check_friend_cache()
{
  if (ids.size() > friend_cache.size()) {
  }
}

string const &Profile::name() const { return profile_name; }

} // fb