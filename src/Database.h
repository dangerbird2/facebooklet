//
// Created by Steven on 4/9/15.
//

#ifndef FACEBOOKLET_DATABASE_H
#define FACEBOOKLET_DATABASE_H

#include "interfaces.h"
#include "FBProfile.h"
#include "Date.h"
#include <map>
#include <vector>


namespace fb {

class Profile;

class Database {
public:
  Database();

  /**
   * @brief destructor
   */
  virtual ~Database();


  Database(Database const &db) = delete;

  Database(Database &&db) : id_count(db.id_count)
  {
    for (auto &&i: db.nodes) {
      nodes.insert(std::move(i));
    }
  }

  IFaceBookletNode *get_node(id_t id);

  IFaceBookletNode *new_node(IFaceBookletNode *node);

  IFaceBookletNode *set_node(id_t id, IFaceBookletNode *node);

  bool has_node(id_t id);

  void remove_node(id_t id);

  std::vector<id_t> ids_with_name(std::string name);

  Profile *insert_profile(std::string const &name, time_t creation_time = 0, Date birthday = Date());

  id_t get_id_count() const;

private:
  std::map<id_t, NodeUptr> nodes;
  id_t id_count;
};

}

#endif // FACEBOOKLET_DATABASE_H
