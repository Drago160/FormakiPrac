#include "gtest/gtest.h"
#include "earley.h"

class HWTester : public ::testing::Test {
 protected:
  void SetUp() {
    G = new CF_Grammar({'T', 'A', 'B', 'C', 'K', 'R'},
                       {'a', 'b'},

                       {{"T", "aA", "bB"},
                        {"A", "aC", "bT"},
                        {"B", "aT", "bK"},
                        {"K", "aB"},
                        {"C", "bA", "aR", ""},
                        {"R", "aRR", "bC"}},

                        'T');
  }
  void TearDown() {
    delete G;
  }
  CF_Grammar* G;

};

TEST_F(HWTester, BasicTest) {
  ASSERT_EQ(earleyRecognize(*G, "aa"), true);
}

TEST_F(HWTester, BasicTest2) {
  ASSERT_EQ(earleyRecognize(*G, "bbaaaa"), true);
}

TEST_F(HWTester, BasicTest3) {
  ASSERT_EQ(earleyRecognize(*G, "baabaa"), true);
}

TEST_F(HWTester, BasicTest4) {
  ASSERT_EQ(earleyRecognize(*G, "abaaab"), true);
}

TEST_F(HWTester, BigDeviation1) {
  ASSERT_EQ(earleyRecognize(*G, "aaaaaaaaaaaaaaaabbbbbbbbbbbbbb"), true);
}

TEST_F(HWTester, Fluctuation1) {
  ASSERT_EQ(earleyRecognize(*G, "bbaabbaabbaaaabbaaaaaabbbb"), true);
}

TEST_F(HWTester, Fluctuation2) {
  ASSERT_EQ(earleyRecognize(*G, "ababababababababababababababababaa"), true);
}

TEST_F(HWTester, LowPref1) {
  ASSERT_EQ(earleyRecognize(*G, "bbbaaaaa"), false);
}

TEST_F(HWTester, LowPref2) {
  ASSERT_EQ(earleyRecognize(*G, "bbabaaaaa"), false);
}

TEST_F(HWTester, LowPref3) {
  ASSERT_EQ(earleyRecognize(*G, "aaaabbbbabbabbabbaaaaaa"), false);
}

TEST_F(HWTester, WrongModule1) {
  ASSERT_EQ(earleyRecognize(*G, "aababababaabaabababababababaaaabaabab"), false);
}

TEST_F(HWTester, WrongModule2) {
  ASSERT_EQ(earleyRecognize(*G, "aababababaabaababababaabaababababaababbababbababbaaaabaaababbabab"), false);
}