/**
 * Created by Steven on 4/9/15.
 * @file
 * @brief FaceBookletDatabase class
 */

#ifndef FB_DATABASE_H
#define FB_DATABASE_H

#include "INode.h"
#include <map>
#include <vector>
#include "Date.h"


namespace fb {

// predeclare Profile class
class Profile;

class Date;

class Database {
public:
  Database();

  virtual ~Database();

  /**
   * @brief copy constructor
   */
  Database(Database const &db);

  Database operator=(Database const &db) { return Database(db); }

  IFaceBookletNode *get_node(id_t id);

  IFaceBookletNode *new_node(IFaceBookletNode *node);

  IFaceBookletNode *set_node(id_t id, IFaceBookletNode *node);

  bool has_node(id_t id);

  void remove_node(id_t id);

  std::vector<id_t> ids_with_name(std::string name);

  Profile *insert_profile(std::string const &name, time_t creation_time,
                          Date const &birthday = Date(1, Month::Jan, 1970));

private:
  std::map<id_t, NodeUptr> nodes;
  id_t id_count;
};

std::map<id_t, NodeUptr> copy_nodemap(std::map<id_t, NodeUptr> const &m);
}

#endif // FB_DATABASE_H
