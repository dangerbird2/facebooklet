#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>
#include <iostream>
#include <memory>

namespace fb {

using id_t = size_t;

struct IFaceBookletNode {

  virtual const id_t get_id() const = 0;

  virtual std::string const &name() const = 0;

  virtual const std::string describe() const = 0;

  virtual IFaceBookletNode const *get_friend(id_t id) const = 0;

  virtual IFaceBookletNode *get_friend(id_t id) = 0;

  virtual void add_friend(IFaceBookletNode &fr) = 0;

  virtual void remove_friend(id_t id) = 0;

  friend std::ostream &operator<<(std::ostream &os,
                                  const IFaceBookletNode &node);

  friend bool operator==(IFaceBookletNode const &self,
                         IFaceBookletNode const &rhs);
};

/**
 * type aliases for smart pointers utilizing IFaceBookletNode
 */
using NodeUptr = std::unique_ptr<IFaceBookletNode>;
using NodeSptr = std::shared_ptr<IFaceBookletNode>;
using NodeWptr = std::weak_ptr<IFaceBookletNode>;

} // fb

#endif // INTERFACES_H
