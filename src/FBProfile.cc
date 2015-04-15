#include <facebooklet/face.h>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

namespace fb {

using namespace std;

Profile::Profile(IDatabase *db, std::string const &name)
    : db(db), profile_name(name), id(0) { }

const id_t Profile::get_id() const { return id; }

string const Profile::describe() const
{
  auto buff = stringstream();
  buff << "{Profile:" << profile_name << " id:" << id << "}";

  return string(buff.str());
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

void Profile::add_friend(IFaceBookletNode *fr)
{

  if (!fr) {
    cerr << "\tfr is nullptr\n";
    return;
  }
  auto friend_id = fr->get_id();

  if (friend_id == id) {

    return;
  }

  if (!get_friend(friend_id)) {
    ids.insert(friend_id);
  }
  // call add friend on friend node if this
  // is not already added
  IFaceBookletNode *fr_fr = fr->get_friend(id);
  if (fr_fr == nullptr || fr_fr != this) {
    printf("%lu\n", (size_t) fr_fr);
    fr->add_friend(this);
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

string const &Profile::get_name() const { return profile_name; }

Profile::~Profile() { }

void Profile::set_id(id_t id)
{
  auto old_id = this->id;
  this->id = id;

  if (ids.size() > 0) {
    // reset friend ids
    for (auto &i: ids) {
      auto fr = db->get_node(i);
      fr->remove_friend(old_id);
      fr->add_friend(this);
    }
  }
}

NodeData &Profile::get_data()
{
  return data;
}

NodeData const &Profile::get_data() const
{
  return data;
}

void Profile::set_data(NodeData const &data)
{
  this->data = data;
}

Profile::Profile() : db(nullptr), profile_name("") { }
} // fb