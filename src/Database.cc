//
// Created by Steven on 4/9/15.
//

#include <facebooklet/face.h>
#include <vector>

namespace fb {

/*
 * Database implementation
 */

Database::Database() { }

IFaceBookletNode *Database::get_node(id_t id) { return nullptr; }

IFaceBookletNode *Database::new_node(IFaceBookletNode *node)
{
  auto id = 1lu;
  auto probing = true;

  // find first unused node_id in database
  while (probing) {
    probing = has_node(id);
    ++id;
  }
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

std::vector<id_t> Database::ids_with_name(std::string name) { return {}; }

Database::~Database() { }
}
