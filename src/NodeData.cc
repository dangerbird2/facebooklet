//
// Created by Steven on 4/14/15.
//

#include "../include/facebooklet/NodeData.h"

#include <facebooklet/face.h>

namespace fb {


/*
 * NodeData implementation
 */

id_t NodeData::get_time() const
{
  return time;
}

NodeData::NodeData(std::string const &name, time_t creation_time, std::vector<NodePost> const &posts) :
    name(name), posts(posts), time(creation_time) { }


void NodeData::set_name(std::string &name)
{
  NodeData::name = name;
}

void NodeData::set_posts(std::vector<NodePost> const &posts)
{
  NodeData::posts = posts;
}

std::vector<NodePost> const &NodeData::get_posts() const
{
  return posts;
}

std::string const &NodeData::get_name()
{
  return name;
}

void NodeData::set_time(id_t time)
{
  NodeData::time = time;
}


/*
 * Equality operators for NodeData and NodePost
 */
bool operator==(NodeData const &lhs, NodeData const &rhs)
{
  return lhs.name == rhs.name &&
         lhs.time == rhs.time &&
         lhs.posts == rhs.posts;
}

bool operator==(NodePost const &lhs, NodePost const &rhs)
{
  return lhs.text == rhs.text &&
         lhs.time == rhs.time;
}

NodeData::NodeData() : NodeData("", 0, {}) { }
}


