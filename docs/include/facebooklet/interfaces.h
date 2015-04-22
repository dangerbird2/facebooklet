/**
 * Steve Shea
 * @file
 * @brief defines interface type for Facebooklet Nodes
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "utils.h"
#include "NodeData.h"

namespace fb {


/**
 * @brief interface class for FaceBooklet nodes
 */
struct IFaceBookletNode {

  virtual ~IFaceBookletNode() { }

  /**
   * @brief returns a copy of the node allocated via new()
   */
  virtual IFaceBookletNode *heap_copy() = 0;

  /**
   * @brief getter for booklet's id tag
   * @returns id value
   */
  virtual const id_t get_id() const = 0;

  /**
   * @brief setter for booklet's id tag.
   * @detail this should be used with caution,
   * as all other relationships depend on node ids.
   * It is probably best to handle id modifications in
   * the host database instance.
   *
   * @param id id number to set
   */
  virtual void set_id(id_t id) = 0;

  /*
   * getters/setters for node's data
   */
  virtual NodeData &get_data() = 0;

  virtual NodeData const &get_data() const = 0;

  virtual void set_data(NodeData const &data) = 0;

  /**
   * @brief get node's description.
   * @detail Used for printing to
   * std::ostream
   */
  virtual std::string const describe() const = 0;

  /**
   * @brief retrieves a friend by id number.
   * @detail const method
   *
   * @param id id of friend
   * @returns pointer to friend node, or if id is not a friend,
   * a nullptr
   */
  virtual IFaceBookletNode *get_friend(id_t id) = 0;

  /**
   * @brief retrieves a friend by id number. const method.
   * @detail const method
   *
   * @param id id of friend
   * @returns pointer to friend node, or if id is not a friend,
   * a nullptr
   */
  virtual IFaceBookletNode const *get_friend(id_t id) const = 0;

  /**
   * @brief indicates if a node has a given friend.
   * @param id id key for friend
   *
   * @return true if id corresponds to the node's friend
   */
  virtual const bool has_friend(id_t id) const = 0;

/**
 * @brief indicates if a node has a given friend.
 * @param node pointer to a IFaceBookletNode
 *
 * @return true if node corresponds to the node's friend
 */
  virtual const bool has_friend(IFaceBookletNode *node) const = 0;

  /**
   * @brief add a friend to node's friend list
   */
  virtual void add_friend(IFaceBookletNode *fr) = 0;


  virtual void remove_friend(id_t id) = 0;

  virtual std::vector<id_t> get_friend_ids() const = 0;

  friend std::ostream &operator<<(std::ostream &os,
                                  const IFaceBookletNode &node);

  friend bool operator==(IFaceBookletNode const &self,
                         IFaceBookletNode const &rhs);

};

bool operator==(IFaceBookletNode const &self,
                IFaceBookletNode const &rhs);

/**
 * type aliases for smart pointers utilizing IFaceBookletNode
 */
using NodeUptr = std::unique_ptr<IFaceBookletNode>;
using NodeSptr = std::shared_ptr<IFaceBookletNode>;
using NodeWptr = std::weak_ptr<IFaceBookletNode>;


} // fb

#endif // INTERFACES_H
