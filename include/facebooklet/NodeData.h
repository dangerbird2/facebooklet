//
// Created by Steven on 4/14/15.
//

#ifndef FB_NODEDATA_H
#define FB_NODEDATA_H

#include <string>
#include <vector>
#include <ctime>
#include "utils.h"

namespace fb {

/**
 * @brief the data for a single post.
 * @details Does not track the user that posted it,
 * nor does it encapsulate any complex behavior.
 * Instead, it is a simple record structure manipulated by
 * other classes
 */
struct NodePost {
  NodePost(const std::string &text, time_t time) :
      text(text), time(time) { }

  std::string text;
  time_t time;

  friend bool operator==(NodePost const &lhs, NodePost const &rhs);
};

/**
 * @brief the class containing a node's basic information and
 * post history.
 * @detail all IFaceBookletNode types use this class
 * for storing object and post history data. (consider how
 * a Facebook wall is functionally identical for people, groups, and
 * pages.)
 */
class NodeData {
public:

  /**
   * @brief default constructor
   */
  NodeData();

  /**
   * @brief parameter constructor
   *
   * @param name name of Node object
   * @param creation_time Unix timestamp of node's creation
   * @param posts vector copied to NodeData's post history
   */
  NodeData(std::string const &name,
           time_t creation_time = 0,
           std::vector<NodePost> const &posts = {});

  /*
   * name getter/setter property
   */
  std::string const &get_name();

  void set_name(std::string &name);

  /*
   * posts getter/setter property
   */
  std::vector<NodePost> const &get_posts() const;

  void set_posts(std::vector<NodePost> const &posts);


  /*
   * time getter/setter property
   */
  void set_time(id_t time);

  id_t get_time() const;

  /*
   * friends
   */
  friend bool operator==(NodeData const &lhs, NodeData const &rhs);

private:
  std::string name;
  std::vector<NodePost> posts;
  time_t time;
};

bool operator==(NodePost const &lhs, NodePost const &rhs);

bool operator==(NodeData const &lhs, NodeData const &rhs);

}


#endif //FB_NODEDATA_H
