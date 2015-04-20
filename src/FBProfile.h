#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "INode.h"
#include "Database.h"
#include "Date.h"
#include <set>
#include <map>

namespace fb {

class Profile : public IFaceBookletNode {
public:

  Profile(Database *db, std::string const &name, Date const &birthday=Date(), time_t time=0);

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

  void set_id(id_t id);


  NodeData &get_data();

  NodeData const &get_data() const;

  void set_data(NodeData const &data);

  const bool has_friend(id_t id) const;

  const bool has_friend(IFaceBookletNode *node) const;

  Date const & get_birthday() const;

  void set_birthday(Date const &birthday);

  /**
   * @brief return copy of the node to the heap.
   * @detail used as a convenience method for copying nodes without knowing
   * their concrete type
   */
  virtual IFaceBookletNode *heap_copy();

private:
  /**
   * object id
   */
  id_t id;


  NodeData data;
  Date birthday;

  /**
   * pointer to database object
   */
  Database *db;

  /**
   * a map of ids with node ids and a boolean indicating
   * whether or not they are friends
   */
  std::map<id_t, bool> friends;
};



} // fb

#endif // FB_PROFILE_H
