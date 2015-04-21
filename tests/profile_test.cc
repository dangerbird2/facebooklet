#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/face.h"
#include <vector>
#include <string>
#include <iostream>
#include <ldap.h>

using namespace std;
using namespace testing;
using namespace fb;


class ProfileTests : public Test {

protected:
  Database db;
  Profile *bob = nullptr;
  Profile *bill = nullptr;

  virtual void SetUp() override
  {
    Test::SetUp();

    bob = db.insert_profile("bob", 0, Date());
    bill = db.insert_profile("bill", 0, Date());
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


TEST_F(ProfileTests, Describe)
{
  auto describe_head = string("{Profile:bill");
  auto actual = bill->describe();

  // make sure bill's description starts with "{Profile:bill"
  EXPECT_EQ(describe_head,
            actual.substr(0, describe_head.size() / sizeof(char)));
}


TEST_F(ProfileTests, DbId)
{
  const auto id = 42;
  bill->set_id(id);

  // assert that bill's new id is 42
  EXPECT_EQ(id, bill->get_id());
}

TEST_F(ProfileTests, GetFriend)
{
  bill->add_friend(bob);

  EXPECT_EQ(bill->get_friend(bob->get_id()),
            bob);

  bill->add_friend(bill);
  // you shouldn't be your own friend
  auto my_own_friend = bill->get_friend(bill->get_id());
  EXPECT_NE(bill, my_own_friend);
  EXPECT_EQ(nullptr, my_own_friend);
}

TEST_F(ProfileTests, AddFriend)
{
  bob->add_friend(bill);
  EXPECT_EQ(bob, bill->get_friend(bob->get_id()));
  EXPECT_EQ(bill, bob->get_friend(bill->get_id()));
}

TEST_F(ProfileTests, RemoveFriend)
{
  bob->add_friend(bill);
  EXPECT_EQ(bill->get_friend(bob->get_id()),
            bob);

  bob->remove_friend(bill->get_id());

  EXPECT_EQ(false, bob->has_friend(bill));
  EXPECT_EQ(false, bill->has_friend(bob));
}

TEST_F(ProfileTests, ProfileEq)
{
  EXPECT_EQ(*bob, *bob);
}