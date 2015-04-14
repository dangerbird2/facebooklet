#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <facebooklet/face.h>
#include <vector>
#include <string>
#include <iostream>
#include <ldap.h>

namespace fb {
using namespace std;
using namespace testing;

namespace fb {
class ProfileTests : public Test {

protected:
  Database db;
  Profile *bob = nullptr;
  Profile *bill = nullptr;

  virtual void SetUp() override
  {
    Test::SetUp();

    bob = static_cast<Profile *>(db.new_node(new Profile(&db, "bob")));
    bill = static_cast<Profile *>(db.new_node(new Profile(&db, "bill")));

  }

  virtual void TearDown()
  {

  }
};

TEST_F(ProfileTests, Construction)
{
  ASSERT_NE(nullptr, bill);
  ASSERT_NE(nullptr, bob);
}

TEST_F(ProfileTests, AddFriend)
{
  bob->add_friend(*bill);
  EXPECT_EQ(bill->get_friend(bob->get_id()),
            bob);
  EXPECT_EQ(bob->get_friend(bill->get_id()),
            bill);
}
}


}