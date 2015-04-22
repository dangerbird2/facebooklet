/**
 * Created by Steven on 4/14/15.
 * @file
 * @brief contains data for building node data
 */

#ifndef FB_NODEDATA_H
#define FB_NODEDATA_H

#include <string>
#include <vector>
#include <ctime>
#include "utils.h"

namespace fb {

/**
 * @brief Record type for storing data of a single post.
 * @details Does not track the user that posted it,
 * nor does it encapsulate any complex behavior.
 * Instead, it is a simple record structure manipulated by
 * other classes
 * 
 * @param text Post text.
 * @param t Time of post creation.
 * @param e [description]
 * @return [description]
 */
struct NodePost {
  NodePost(const std::string &text, time_t t) :
      text(std::string(text)), time(t) { }

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

  NodeData(NodeData const &data);

  NodeData operator=(NodeData const &data);

  ~NodeData() { }

  /*
   * name getter/setter property
   */
  std::string const &get_name() const;

  void set_name(std::string &name);

  /*
   * posts getter/setter property
   */
  std::vector<NodePost> const &get_posts() const;

  void set_posts(std::vector<NodePost> const &posts);


  /**
   * @brief sets time property
   * @param t time related to c time() function
   */
  void set_time(time_t t);

  /**
   * @brief gets time property
   * @return [description]
   */
  time_t get_time() const;

  /*
   * friends
   */
  friend bool operator==(NodeData const &lhs, NodeData const &rhs);

private:
  std::string name;
  std::vector<NodePost> posts;
  time_t time;
};

/**
 * @brief equality operator for NodePost
 */
bool operator==(NodePost const &lhs, NodePost const &rhs);

/**
 * @brief equality operator for NodeData
 */
bool operator==(NodeData const &lhs, NodeData const &rhs);

}


#endif //FB_NODEDATA_H
