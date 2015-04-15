#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "interfaces.h"
#include "Database.h"
#include <set>
#include <map>

namespace fb {

class Profile : public IFaceBookletNode {
public:

  Profile(IDatabase *db, std::string const &name);

  Profile();

  virtual ~Profile();

  const id_t get_id() const;

  std::string const describe() const;

  IFaceBookletNode const *get_friend(id_t id) const;

  IFaceBookletNode *get_friend(id_t id);

  void add_friend(IFaceBookletNode *fr);

  void remove_friend(id_t id);

  void set_id(id_t id);

  std::string const &get_name() const;


  NodeData &get_data();

  NodeData const &get_data() const;

  void set_data(NodeData const &data);

private:
  std::string profile_name;
  id_t id;

  NodeData data;

  IDatabase *db;

  /**
   * a set-hashtable of ids associated with the profile
   * the Profile class does not contain pointers to
   * any other profiles. Instead, it uses a database class to
   * manage relationships
   */
  std::set<id_t> ids;
};

} // fb

#endif // FB_PROFILE_H
