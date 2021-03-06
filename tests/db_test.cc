//
// Created by Steven on 4/10/15.
//

#include "../src/face.h"
#include <gtest/gtest.h>
#include <algorithm>

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
    pr1 = db.insert_profile("bob", time(NULL));
    pr2 = db.insert_profile("bill", time(NULL) - 100);

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

TEST_F(DbTest, FindNodes)
{
  auto id1 = db.insert_profile("joe")->get_id();
  auto id2 = db.insert_profile("joe")->get_id();

  auto search = db.ids_with_name("joe");

  ASSERT_TRUE(db.has_node(id1));

  EXPECT_EQ(2, search.size());
  EXPECT_EQ(1, count(search.begin(), search.end(), id1));
  EXPECT_EQ(1, count(search.begin(), search.end(), id2));


}
