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

  virtual const id_t get_id() const;

  virtual std::string const describe() const;

  virtual IFaceBookletNode const *get_friend(id_t id) const;
  virtual IFaceBookletNode *get_friend(id_t id);

  virtual void add_friend(IFaceBookletNode &fr);
  virtual void remove_friend(id_t id);

  virtual void set_id(id_t id);

  virtual std::string const &get_name() const;


  virtual NodeData &get_data();

  virtual NodeData const &get_data() const;

  virtual void set_data(NodeData const &data);

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
