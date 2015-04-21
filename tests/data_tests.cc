
/**
 * Created by Steven on 4/20/15.
 */

#include <gtest/gtest.h>
#include "../src/face.h"

using namespace fb;
using namespace std;
using namespace testing;

class DataTests: public Test {
protected:
  virtual void SetUp()
  {
    Test::SetUp();

  }
};

/*
TEST_F(DataTests, PostData) {
  auto data1 = NodePost("hello", 0);
  auto data2 = NodePost("hello", 0);
  auto data3 = NodePost("world", 0);
  auto data4 = NodePost("hello", 1);

  EXPECT_EQ(data1, data2);
  EXPECT_NE(data1, data3);
  EXPECT_NE(data1, data4);
}

*/
