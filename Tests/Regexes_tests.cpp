#include "gtest/gtest.h"
#include "earley.h"

class Regex1 : public ::testing::Test {
 protected:
  void SetUp() {
    G1 = new CF_Grammar("S->aA|Aa|A;A->aA|a;");
  }
  CF_Grammar* G1; // a+
};

class Regex2 : public ::testing::Test {
 protected:
  void SetUp() {
    G2 = new CF_Grammar("S->aB|b;B->bB|bS|bb;");
  }
  CF_Grammar* G2; // (ab+)*b
};


class Regex3 : public ::testing::Test {
 protected:
  void SetUp() {
    G3 = new CF_Grammar("S->aS|bS|B;B->bbC;C->aC|bC|aa|ba");
  }
  CF_Grammar* G3; // (a+b)*bb(a+b)+a
};


TEST_F(Regex1, Test1) {
  ASSERT_EQ(earleyRecognize(*G1, "a"), true);
}

TEST_F(Regex1, Test2) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaa"), true);
}

TEST_F(Regex1, Test3) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaaaaaaaaaa"), true);
}

TEST_F(Regex1, Test4) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), true);
}

TEST_F(Regex1, Test5) {
  ASSERT_EQ(earleyRecognize(*G1, "b"), false);
}

TEST_F(Regex1, Test6) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaab"), false);
}

TEST_F(Regex1, Test7) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaaaaaaaaaaaaaaaab"), false);
}

TEST_F(Regex1, Test8) {
  ASSERT_EQ(earleyRecognize(*G1, "aaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), false);
}

TEST_F(Regex2, Test1) {
  ASSERT_EQ(earleyRecognize(*G2, "abb"), true);
}

TEST_F(Regex2, Test2) {
  ASSERT_EQ(earleyRecognize(*G2, "b"), true);
}

TEST_F(Regex2, Test3) {
  ASSERT_EQ(earleyRecognize(*G2, "abbabbabb"), true);
}

TEST_F(Regex2, Test4) {
  ASSERT_EQ(earleyRecognize(*G2, "abbbbbbbbabbbbbbbbbabbbbbbbbbbbabbbbbbb"), true);
}

TEST_F(Regex2, Test5) {
  ASSERT_EQ(earleyRecognize(*G2, "abababababababbbbbbbbbabbbbbbbababababababababbbbbbbbabbbbbbbbbabbbbbbbbbbbabbbbbbb"), true);
}

TEST_F(Regex2, Test6) {
  ASSERT_EQ(earleyRecognize(*G2, "aabababababbbaaaaaa"), false);
}

TEST_F(Regex2, Test7) {
  ASSERT_EQ(earleyRecognize(*G2, "a"), false);
}

TEST_F(Regex2, Test8) {
  ASSERT_EQ(earleyRecognize(*G2, ""), false);
}

TEST_F(Regex2, Test9) {
  ASSERT_EQ(earleyRecognize(*G2, "bbbaaaaaaaaa"), false);
}


// (a+b)*bb(a+b)+a
TEST_F(Regex3, Test1) {
  ASSERT_EQ(earleyRecognize(*G3, "bbaa"), true);
}

TEST_F(Regex3, Test2) {
  ASSERT_EQ(earleyRecognize(*G3, "abaabababbba"), true);
}

TEST_F(Regex3, Test3) {
  ASSERT_EQ(earleyRecognize(*G3, "aaaaaaabbaa"), true);
}

TEST_F(Regex3, Test4) {
  ASSERT_EQ(earleyRecognize(*G3, "aabababababbabbabababaaaabbabababbabababbabbbaa"), true);
}

TEST_F(Regex3, Test5) {
  ASSERT_EQ(earleyRecognize(*G3, "bbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), true);
}

TEST_F(Regex3, Test6) {
  ASSERT_EQ(earleyRecognize(*G3, "aaabaa"), false);
}

TEST_F(Regex3, Test7) {
  ASSERT_EQ(earleyRecognize(*G3, "aaabba"), false);
}

TEST_F(Regex3, Test8) {
  ASSERT_EQ(earleyRecognize(*G3, "aaabaa"), false);
}

TEST_F(Regex3, Test9) {
  ASSERT_EQ(earleyRecognize(*G3, "bbbbbbbbbbbbbbbb"), false);
}