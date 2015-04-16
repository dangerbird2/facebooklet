//
// Created by Steven on 4/10/15.
//

#include "../src/face.h"
#include <gtest/gtest.h>

using namespace fb;
using namespace std;
using namespace testing;

class DbTest : public Test {
protected:
  Database db;
  IFaceBookletNode *pr1;
  IFaceBookletNode *pr2;

  virtual void SetUp()
  {
    pr1 = db.new_node(new Profile(&db, "bob"));
    pr2 = db.new_node(new Profile(&db, "joe"));

  }

  virtual void TearDown()
  {

  }
};

/**
 * tries inserting a pr1, and retrieving
 */
TEST_F(DbTest, GetNode)
{
  auto p2 = db.get_node(pr1->get_id());

  ASSERT_NE(nullptr, pr1);

  EXPECT_EQ(pr1->get_id(), pr1->get_id());
  EXPECT_EQ(pr1->get_data().get_name(), p2->get_data().get_name());
  EXPECT_EQ(pr1, p2);
}