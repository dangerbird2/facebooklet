#include "face.h"
#include <sstream>
#include <assert.h>

namespace fb {

using namespace std;

Profile::Profile(IDatabase *db, std::string const &name, time_t time)
    : db(db), id(0)
{
  data = NodeData(name, time);
}

const id_t Profile::get_id() const { return id; }

string const Profile::describe() const
{
  auto buff = stringstream();
  buff << "{Profile:" << data.get_name() << " id:" << id << "}";

  return string(buff.str());
}

IFaceBookletNode const *Profile::get_friend(id_t id) const
{
  auto node = (IFaceBookletNode *) nullptr;

  // ensures id is in friends, and that its value is true

  if (db && has_friend(id)) {
    node = db->get_node(id);
  }

  return node;
}

IFaceBookletNode *Profile::get_friend(id_t fr_id)
{
  auto node = (IFaceBookletNode*) nullptr;


  if (db && has_friend(fr_id)) {
    node = db->get_node(fr_id);
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

  if (friend_id == id || fr == this) {
    cerr << "\nnode fr == this";
    return;
  }

  if (!get_friend(friend_id)) {
    friends[friend_id] = true;
  }
  // call add friend on friend node if this
  // is not already added
  IFaceBookletNode *fr_fr = fr->get_friend(id);
  if (fr_fr == nullptr || fr_fr != this) {
    fr->add_friend(this);
  }
}

void Profile::remove_friend(id_t fr_id)
{
  auto fr = get_friend(id);
  if (fr) {
    friends.at(id) = false;

    if (fr->has_friend(id)) {
      fr->remove_friend(id);
    }


  }
}

Profile::~Profile() { }

void Profile::set_id(id_t id)
{
  auto old_id = this->id;
  this->id = id;

  if (friends.size() > 0) {
    // reset friend ids
    for (auto &i: friends) {
      auto fr = db->get_node(i.first);
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

Profile::Profile() : Profile(nullptr, "", 0) { }

const bool Profile::has_friend(id_t id) const
{
  auto res = false;
  try {
    res = friends.at(id);
  } catch (std::out_of_range const &e) { // key does not exist
    res = false;
  }
  return res;
}

const bool Profile::has_friend(IFaceBookletNode *node) const
{
  return has_friend(node->get_id());
}
} // fb