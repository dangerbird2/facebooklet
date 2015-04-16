//
// Created by Steven on 4/9/15.
//

#ifndef ANIMAL_DATABASE_H
#define ANIMAL_DATABASE_H

#include "interfaces.h"
#include "FBProfile.h"
#include <map>
#include <vector>


namespace fb {

class Profile;

class Database : public IDatabase {
public:
  Database();

  virtual ~Database();

  Database(Database &db) = delete;

  IFaceBookletNode *get_node(id_t id);

  IFaceBookletNode *new_node(IFaceBookletNode *node);

  IFaceBookletNode *set_node(id_t id, IFaceBookletNode *node);

  bool has_node(id_t id);

  void remove_node(id_t id);

  std::vector<id_t> ids_with_name(std::string name);

  Profile *insert_profile(std::string const &name, time_t creation_time);

private:
  std::map<id_t, NodeUptr> nodes;
  id_t id_count;
};
}

#endif // ANIMAL_DATABASE_H
