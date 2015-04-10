//
// Created by Steven on 4/9/15.
//

#include <facebooklet/face.h>
#include <vector>

namespace fb {

Database::Database() { }

IFaceBookletNode *Database::get_node(id_t id) { return nullptr; }

void fb::Database::set_node(id_t id, NodeUptr node)
{
  if (!node) {
    return;
  }
  remove_node(id);
  nodes[id] = std::move(node);
}

bool Database::has_node(id_t id) { return nodes.count(id) > 0; }

void Database::remove_node(id_t id)
{
  if (has_node(id)) {
    nodes.erase(id);
  }
}

std::vector<id_t> Database::ids_with_name(std::string name) { return {}; }
}