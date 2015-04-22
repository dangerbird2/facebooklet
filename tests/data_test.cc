//
// Created by Steven on 4/21/15.

//

#include <gtest/gtest.h>

#include "../src/face.h"

using namespace fb;

TEST(DataTest, Name)
{
  auto name = "bill";
  auto data = NodeData(name);
  EXPECT_EQ(name, data.get_name());
}