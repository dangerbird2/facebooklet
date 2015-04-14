//
// Created by Steven on 4/9/15.
//

#ifndef ANIMAL_DATABASE_H
#define ANIMAL_DATABASE_H

#include "interfaces.h"
#include <map>
#include <vector>

namespace fb {
class Database : public IDatabase {
public:
  Database();

  virtual ~Database();

  Database(Database &db) = delete;

  virtual IFaceBookletNode *get_node(id_t id);

  virtual IFaceBookletNode *new_node(IFaceBookletNode *node);

  virtual IFaceBookletNode *set_node(id_t id, IFaceBookletNode *node);

  virtual bool has_node(id_t id);

  virtual void remove_node(id_t id);

  std::vector<id_t> ids_with_name(std::string name);

private:
  std::map<id_t, NodeUptr> nodes;
};
}

#endif // ANIMAL_DATABASE_H
