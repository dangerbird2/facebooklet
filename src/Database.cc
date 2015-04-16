//
// Created by Steven on 4/9/15.
//

#include "face.h"
#include <vector>
#include <memory>

namespace fb {

using namespace std;

/*
 * Database implementation
 */

Database::Database() : id_count(0) { }

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
  nodes[id] = std::unique_ptr<IFaceBookletNode>(node);
  return nodes[id].get();
}

bool Database::has_node(id_t id) { return nodes.count(id) > 0; }

void Database::remove_node(id_t id)
{
  if (has_node(id)) {
    nodes.erase(id);
  }
}

Profile *Database::insert_profile(std::string const &name,
                                  time_t creation_time = 0)
{
  auto profile = new Profile(this, name);


  return (Profile *) new_node(profile);
}

std::vector<id_t> Database::ids_with_name(std::string name) { return {}; }

Database::~Database() { }
}
