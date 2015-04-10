#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "interfaces.h"
#include "Database.h"
#include <set>
#include <map>

namespace fb {

class Profile : public IFaceBookletNode {
public:
  Profile(Database *db, std::string const &name);

  Profile(): db(nullptr), profile_name("") { }

  virtual const id_t get_id() const;

  virtual const std::string describe() const;

  virtual IFaceBookletNode const *get_friend(id_t id) const;

  virtual IFaceBookletNode *get_friend(id_t id);

  virtual void add_friend(IFaceBookletNode &fr);

  virtual void remove_friend(id_t id);

  virtual std::string const &name() const;

private:
  std::string profile_name;
  id_t id;

  Database *db;

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
