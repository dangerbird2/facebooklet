#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "interfaces.h"
#include "Database.h"

namespace fb {

class Profile : public IFaceBookletNode {
public:
  Profile(Database *db, std::string const &name);

  Profile() { }

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

  // ensures id set matches to
  void check_friend_cache();

  std::map<id_t, id_t> ids;
  std::map<id_t, IFaceBookletNode *> friend_cache;
};

} // fb

#endif // FB_PROFILE_H
