#include "gtest/gtest.h"
#include "earley.h"

class CW_Tester : public ::testing::Test {
 protected:
  void SetUp() {
    G = new CF_Grammar("S->A|AA|AAA;A->bAA|cAA|aC;C->aB|bA|cA|;B->bC|cC|aBB;"); // |w|_a - |w|_b - |w|_c \in {1, 2, 3}
  }
  CF_Grammar* G;
  void TearDown() {
    delete G;
  }
};

TEST_F(CW_Tester, basic1) {
ASSERT_EQ(earleyRecognize(*G, "a"), true);
}
TEST_F(CW_Tester, basic2) {
ASSERT_EQ(earleyRecognize(*G, "b"), false);
}
TEST_F(CW_Tester, basic3) {
ASSERT_EQ(earleyRecognize(*G, "bcaa"), false);
}
TEST_F(CW_Tester, basic4) {
ASSERT_EQ(earleyRecognize(*G, "abaca"), true);
}
TEST_F(CW_Tester, basic5) {
ASSERT_EQ(earleyRecognize(*G, "aaaba"), true);
}

TEST_F(CW_Tester, medium_test1) {
ASSERT_EQ(earleyRecognize(*G, "bbaaabaabababcabaa"), true);
}

TEST_F(CW_Tester, medium_test2) {
ASSERT_EQ(earleyRecognize(*G, "aaaaaaaaaabbbbbcccccaa"), true);
}

TEST_F(CW_Tester, medium_test3) {
ASSERT_EQ(earleyRecognize(*G, "aaaaaaaaaaaaabbbbbcccccaa"), false);
}

TEST_F(CW_Tester, long_test1) {
ASSERT_EQ(earleyRecognize(*G, "abcabacabacabacabacabacabacabacabacabacabacaca"), false);
}

TEST_F(CW_Tester, long_test2) {
ASSERT_EQ(earleyRecognize(*G, "aaaababababababbabaababbabaababbabaababbaba"), true);
}

TEST_F(CW_Tester, long_test3) {
ASSERT_EQ(earleyRecognize(*G, "aaaabababababababababbabaabcacacaabbabaababbabaababbaaaabbbbaaaabbbbaaaabbbbaaaabbbbaba"), true);
}

TEST_F(CW_Tester, long_test4) {
ASSERT_EQ(earleyRecognize(*G, "aaaabababababababababbabaabcacacaabbabaababbabaababbaaaabbbbaaaabbbbaaaabbbbaaaabbbbabaa"), false);
}

TEST_F(CW_Tester, long_test5) {
ASSERT_EQ(earleyRecognize(*G, "aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbba"), true);
}

TEST_F(CW_Tester, long_test6) {
ASSERT_EQ(earleyRecognize(*G, "aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb"), false);
}