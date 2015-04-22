//
// Created by Steven on 4/21/15.
//

#include <gtest/gtest.h>
#include "../src/face.h"
#include <string>
#include <sstream>

using namespace fb;
using namespace std;

class EngineTests : public testing::Test {
protected:


  FaceBooklet *fb;
  stringstream stream;
  Prompter prompter;

  virtual void TearDown()
  {
    if (fb) {
      delete fb;
    }
  }

  virtual void SetUp()
  {
    fb = new FaceBooklet();
    stream = stringstream();
    prompter = Prompter(fb->get_db());
  }

};


TEST_F(EngineTests, PromptUsername)
{
  ASSERT_NE(nullptr, fb->get_db());

  auto t = time(NULL);

  auto profile = (Profile *) nullptr;

  // push response into string stream
  stream << "bob" << endl;

  profile = prompter.create_profile(stream);
  ASSERT_NE(nullptr, profile);
  EXPECT_EQ("bob", profile->get_data().get_name());
  EXPECT_NEAR(t, profile->get_data().get_time(), 30); // bob should have been created around t time

}

TEST_F(EngineTests, Choice)
{
  vector<string> choices = {
      "zero",
      "one",
      "two",
      "three"
  };

  // push an invalid response, then a valid response
  stream << "10000\n1";
  auto choice = prompter.prompt_choice(stream, choices);
  EXPECT_EQ(1, choice);
}