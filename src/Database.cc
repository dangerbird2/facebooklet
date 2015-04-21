//
// Created by Steven on 4/9/15.
//

#include "face.h"
#include <vector>
#include <map>
#include <time.h>
#include <valarray>
#include <assert.h>

namespace fb {

using namespace std;

/*
 * Database implementation
 */

Database::Database() : id_count(0) { }

Database::Database(Database const &db): id_count(db.id_count), nodes(copy_nodemap(db.nodes)) {}

Database Database::operator=(Database const &db) {return Database(db);}

Database::~Database() {
  for (auto &p: nodes) {
    if (p.second) {
      delete p.second;
    }
  }
}

IFaceBookletNode *Database::get_node(id_t id)
{
  auto node = (IFaceBookletNode *) nullptr;

  if (has_node(id)) {
    node = nodes[id];
  }

  return node;
}


IFaceBookletNode *Database::new_node(IFaceBookletNode *node)
{
  if (!node) {return nullptr;}
  auto id = ++id_count;

  return set_node(id, node);
}



IFaceBookletNode *fb::Database::set_node(id_t id, IFaceBookletNode *node)
{
  if (!node) {
    return nullptr;
  }
  if (id != node->get_id()) {
    node->set_id(id);
  }
  remove_node(id);
  nodes.insert(make_pair(id, node));

  assert(nodes.at(id));

  return node;
}

bool Database::has_node(id_t id) { return nodes.count(id) > 0; }

void Database::remove_node(id_t id)
{
  if (has_node(id)) {
    nodes.erase(id);
  }
}

Profile *Database::insert_profile(std::string const &name,
                                  time_t creation_time,
                                  Date const & birthday)
{
  auto profile = Profile(this, name, birthday, creation_time);

  return (Profile *) new_node(profile.heap_copy());
}

std::vector<id_t> Database::ids_with_name(std::string name)
{
  auto ids = vector<id_t>();

  for (auto const &p: nodes) {
    if (p.second->get_data().get_name() == name) {
      ids.push_back(p.first);
    }
  }
  return ids;
}




map<id_t, IFaceBookletNode *> copy_nodemap
    (map<id_t, IFaceBookletNode *> const &mp)
{
  // copy the node table
  auto cpy = map<id_t, IFaceBookletNode*>();

  for (auto const &p: mp) {
    if (p.second) {
      cpy.insert(make_pair(p.first, p.second->heap_copy()));
    }
  }

  return cpy;
}

}
