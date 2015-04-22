/**
 * Steve Shea
 * @file
 * @brief definition for concrete Profile type
 */

#ifndef FB_PROFILE_H
#define FB_PROFILE_H

#include "interfaces.h"
#include "Database.h"
#include "util.h"
#include "Date.h"
#include <set>
#include <map>

namespace fb {

/**
 * @brief Facebooklet profile class.
 * @details Represents a user
 * 
 * @param db pointer to the database which
 * the object will be added to
 * @param name user name
 * @param birthday user birthday
 * @param time time of creation.
 */
class Profile : public IFaceBookletNode {
public:

  Profile(Database *db, std::string const &name, time_t time = 0, Date birthday = Date());

  Profile();

  virtual ~Profile();

  /***********************************
   * implementation of IFaceBookletNode virtual methods
   ************************************/
  /**
   * @brief getter for booklet's id tag
   * @returns id value
   */
  const id_t get_id() const;

  /**
   * @brief setter for booklet's id tag.
   * @details this should be used with caution,
   * as all other relationships depend on node ids.
   * It is probably best to handle id modifications in
   * the host database instance.
   *
   * @param id id number to set
   */
  void set_id(id_t id);

  /**
   * @brief get node's description.
   * @details Used for printing to
   * std::ostream
   */
  std::string const describe() const;

  virtual IFaceBookletNode *heap_copy();

/**
   * @brief retrieves a friend by id number.
   * @details const method
   *
   * @param id id of friend
   * @returns pointer to friend node, or if id is not a friend,
   * a nullptr
   */
  IFaceBookletNode const *get_friend(id_t id) const;

  /**
   * @brief retrieves a friend by id number. const method.
   * @details const method
   *
   * @param id id of friend
   * @returns pointer to friend node, or if id is not a friend,
   * a nullptr
   */
  IFaceBookletNode *get_friend(id_t fr_id);

  void add_friend(IFaceBookletNode *fr);
  void remove_friend(id_t id);


  NodeData &get_data();
  NodeData const &get_data() const;
  void set_data(NodeData const &data);

  /**
   * @brief indicates if a node has a given friend.
   * @param id id key for friend
   *
   * @return true if id corresponds to the node's friend
   */
  const bool has_friend(id_t id) const;

  /**
    * @brief indicates if a node has a given friend.
   * @param node pointer to a IFaceBookletNode
   *
   * @return true if node corresponds to the node's friend
   */
  const bool has_friend(IFaceBookletNode *node) const;

private:
  /**
   * object id
   */
  id_t id;

  Date birthday;

  NodeData data;

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
