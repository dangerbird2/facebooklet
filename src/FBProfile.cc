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

IFaceBookletNode *Profile::get_friend(id_t id) {
  auto node = (IFaceBookletNode*) nullptr;

  auto has_friend = bool(ids.count(id) > 0);

  if (db && has_friend) {
    node = db->get_node(id);
  }

  return node;
}

void Profile::add_friend(IFaceBookletNode &fr) {
  auto friend_id = fr.get_id();
  if (!get_friend(friend_id)) {
    ids.insert(friend_id);
  }
  // call add friend on friend node if this
  // is not already added
  if (!fr.get_friend(id)) {
    fr.add_friend(*this);
  }
}

void Profile::remove_friend(id_t id) {
  auto fr = get_friend(id);
  if (fr) {
    auto fr_id = fr->get_id();
    ids.erase(fr_id);

    if (fr->get_friend(id)) {
      fr->remove_friend(id);
    }
  }
}

string const &Profile::name() const { return profile_name; }

} // fb