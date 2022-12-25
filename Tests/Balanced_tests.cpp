#include "gtest/gtest.h"
#include "earley.h"

class BalancedTest : public ::testing::Test {
 protected:
  void SetUp() {
    G = new CF_Grammar("S->aA|bB|;A->aAA|bS|a;B->bBB|aS|b;");
  }
  CF_Grammar* G;
};

TEST_F(BalancedTest, BasicTest1) {
  ASSERT_EQ(earleyRecognize(*G, ""), true);
}

TEST_F(BalancedTest, BasicTest2) {
  ASSERT_EQ(earleyRecognize(*G, "ab"), true);
}

TEST_F(BalancedTest, twoBlocks) {
  ASSERT_EQ(earleyRecognize(*G, "bbbbaaaa"), true);
}

TEST_F(BalancedTest, someBlocks) {
  ASSERT_EQ(earleyRecognize(*G, "bbbbaaaa"), true);
}

TEST_F(BalancedTest, LongTest) {
  ASSERT_EQ(earleyRecognize(*G, "abbaabbabaabbaabbaabbaabbaabbaabbaabbaabbaababababababbbbaaaababbababa"), true);
}

TEST_F(BalancedTest, RandomTests) {
  int balance = 0;
  const size_t num_of_tests = 10;
  std::string s;
  const size_t max_size = 50;
  for (size_t k = 0; k < num_of_tests; ++k) {
    s = "";
    balance = 0;
    while (s.size() < max_size) {
      if (rand() % 2 == 1) {
        s.push_back('a');
        ++balance;
      } else {
        s.push_back('b');
        --balance;
      }
    }
    while (balance > 0) {
      s.push_back('b');
      --balance;
    }
    while (balance < 0) {
      s.push_back('a');
      ++balance;
    }
    ASSERT_EQ(earleyRecognize(*G, s), true);
  }
}

TEST_F(BalancedTest, BasicTest3) {
  ASSERT_EQ(earleyRecognize(*G, "b"), false);
}

TEST_F(BalancedTest, BasicTest4) {
  ASSERT_EQ(earleyRecognize(*G, "bab"), false);
}

TEST_F(BalancedTest, twoBlock2) {
  ASSERT_EQ(earleyRecognize(*G, "bbbbaaaaa"), false);
}

TEST_F(BalancedTest, twoBlock3) {
  ASSERT_EQ(earleyRecognize(*G, "bbbbbaaaa"), false);
}

TEST_F(BalancedTest, LongTest2) {
  ASSERT_EQ(earleyRecognize(*G, "bbbbbaaabababababbababababaaabababbabbbabababababbaaaaaaaababbabbabbabababbabaa"), false);
}

TEST_F(BalancedTest, LongTest3) {
  ASSERT_EQ(earleyRecognize(*G, "bbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaababababbaaaaaaaababbabbabbabababbabaa"), false);
}