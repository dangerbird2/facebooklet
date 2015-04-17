#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "interfaces.h"
#include "Database.h"
#include <set>
#include <map>

namespace fb {

class Profile : public IFaceBookletNode {
public:

  Profile(IDatabase *db, std::string const &name, time_t time = 0);

  Profile();

  virtual ~Profile();

  /***********************************
   * implementation of IFaceBookletNode virtual methods
   ************************************/

  const id_t get_id() const;

  std::string const describe() const;

  IFaceBookletNode const *get_friend(id_t id) const;
  IFaceBookletNode *get_friend(id_t fr_id);

  void add_friend(IFaceBookletNode *fr);
  void remove_friend(id_t id);

  void set_id(id_t new_id);

  NodeData &get_data();
  NodeData const &get_data() const;
  void set_data(NodeData const &data);


  const bool has_friend(id_t id) const;

  const bool has_friend(IFaceBookletNode *node) const;

private:
  /**
   * object id
   */
  id_t id;

  NodeData data;

  /**
   * pointer to database object
   */
  IDatabase *db;

  /**
   * a map of ids with node ids and a boolean indicating
   * whether or not they are friends
   */
  std::map<id_t, bool> friends;
};

} // fb

#endif // FB_PROFILE_H
