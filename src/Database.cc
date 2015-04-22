//
// Created by Steven on 4/9/15.
//

#include "face.h"
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>
#include <memory>

namespace fb {

using namespace std;

/*
 * Database implementation
 */

Database::Database() : id_count(0) { }

Database::~Database()
{
}

IFaceBookletNode *Database::get_node(id_t id)
{
  auto node = (IFaceBookletNode *) nullptr;

  if (has_node(id)) {
    node = nodes[id].get();
  }

  return node;
}


IFaceBookletNode *Database::new_node(IFaceBookletNode *node)
{
  if (!node) { return nullptr; }
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
  nodes.insert(make_pair(id, move(NodeUptr(node))));

  assert(nodes.at(id));

  return node;
}

bool Database::has_node(id_t id)
{
  return nodes.count(id) > 0;
}

void Database::remove_node(id_t id)
{
  if (has_node(id)) {
    nodes.erase(id);
  }
}

Profile *Database::insert_profile(std::string const &name,
                                  time_t creation_time,
                                  Date birthday)
{
  auto profile = Profile(this, name, creation_time, birthday);

  return (Profile *) new_node(profile.heap_copy());
}

std::vector<id_t> Database::ids_with_name(std::string name)
{
  auto ids = vector<id_t>();
  for (auto const &i: nodes) {
    if (!i.second) { continue; }
    auto name2 = i.second->get_data().get_name();
    if (name2 == name) {
      ids.push_back(i.first);
    }
  }
  return ids;
}

id_t Database::get_id_count() const
{
  return id_count;
}
}
