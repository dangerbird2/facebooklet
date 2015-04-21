//
// Created by Steven on 4/14/15.
//

#include "NodeData.h"

#include "face.h"

namespace fb {


/*
 * NodeData implementation
 */

time_t NodeData::get_time() const
{
  return time;
}

NodeData::NodeData(std::string const &name, time_t creation_time, std::vector<NodePost> const &posts) :
    name(name), posts(posts), time(creation_time) { }

NodeData::NodeData(NodeData const &data)
:name(data.name), posts(data.posts), time(data.time)
{}
NodeData NodeData::operator=(NodeData const &data){return NodeData(data);}

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

std::string const &NodeData::get_name() const
{
  return name;
}

void NodeData::set_time(time_t time)
{
  this->time = time;
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


