#include "gtest/gtest.h"
#include "earley.h"

class DiffPspTest : public ::testing::Test {
 protected:
  void SetUp() {
    G = new CF_Grammar("S->(S)S|[S]S|{S}S|;");
    G1 = new CF_Grammar("S->(F)F|[F]F|{F}F|;F->(F)F|[F]F|{F}F|;");
  }
  CF_Grammar* G;
  CF_Grammar* G1;
};

TEST_F(DiffPspTest, BasicTest1) {
  ASSERT_EQ(earleyRecognize(*G, "{([])}"), true);
}

TEST_F(DiffPspTest, BasicTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "{([])}"), true);
}

TEST_F(DiffPspTest, BasicTest3) {
  ASSERT_EQ(earleyRecognize(*G, "{([)}"), false);
}

TEST_F(DiffPspTest, BasicTest4) {
  ASSERT_EQ(earleyRecognize(*G1, "{([)}"), false);
}


TEST_F(DiffPspTest, LittleTest1) {
  ASSERT_EQ(earleyRecognize(*G, "{}[]{{}}()"), true);
}

TEST_F(DiffPspTest, LittleTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "{}[]{{}}()"), true);
}

TEST_F(DiffPspTest, LittleTest3) {
  ASSERT_EQ(earleyRecognize(*G, "{}[]{}{()]"), false);
}

TEST_F(DiffPspTest, LittleTest4) {
  ASSERT_EQ(earleyRecognize(*G1, "{}[]{}{()]"), false);
}

TEST_F(DiffPspTest, LittleTest5) {
  ASSERT_EQ(earleyRecognize(*G1, "{}[{{}()}]"), true);
}

TEST_F(DiffPspTest, LittleTest6) {
  ASSERT_EQ(earleyRecognize(*G, "{}[{{}()}]"), true);
}

TEST_F(DiffPspTest, LittleTest7) {
  ASSERT_EQ(earleyRecognize(*G1, "{}[{}()}"), false);
}

TEST_F(DiffPspTest, LittleTest8) {
  ASSERT_EQ(earleyRecognize(*G, "{}[{}()}"), false);
}

TEST_F(DiffPspTest, LittleTest9) {
  ASSERT_EQ(earleyRecognize(*G, "{}[]{{}}()"), true);
}

TEST_F(DiffPspTest, LittleTest10) {
  ASSERT_EQ(earleyRecognize(*G1, "{}[]{{}}()"), true);
}

TEST_F(DiffPspTest, MediumTest1) {
  ASSERT_EQ(earleyRecognize(*G, "[()][()]{}[[((({}{})))]]{}[()][()]"), true);
}

TEST_F(DiffPspTest, MediumTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "[()][()]{}[[((({}{})))]]{}[()][()]"), true);
}

TEST_F(DiffPspTest, MediumTest3) {
  ASSERT_EQ(earleyRecognize(*G, "[()][)]{}[[(({}{}))]]{}[)][()]"), false);
}

TEST_F(DiffPspTest, MediumTest4) {
  ASSERT_EQ(earleyRecognize(*G1, "[()][()]{[[(((}{}))]]{}()][()]"), false);
}

TEST_F(DiffPspTest, LongTest1) {
  ASSERT_EQ(earleyRecognize(*G, "(([{}[(({}))]{}](())[[]]([{{}[[]]{}}])))"), true);
}

TEST_F(DiffPspTest, LongTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "(([{}[(({}))]{}](())[[]]([{{}[[]]{}}])))"), true);
}


TEST_F(DiffPspTest, LongTest3) {
  ASSERT_EQ(earleyRecognize(*G, "(([{}(({}))]{}]())[[]]([{}[[]]{}})))"), false);
}

TEST_F(DiffPspTest, LongTest4) {
  ASSERT_EQ(earleyRecognize(*G1, "(([{[(({}))]{}(())[[]]([{}[[]]{}})))"), false);
}

TEST_F(DiffPspTest, LongTest5) {
  ASSERT_EQ(earleyRecognize(*G, "(())[][]{{{}}}{{(([[][]]))}}{{(())}}{}{}()()()()[][]"), true);
}

TEST_F(DiffPspTest, LongTest6) {
  ASSERT_EQ(earleyRecognize(*G1, "(())[][]{{{}}}{{(([[][]]))}}{{(())}}{}{}()()()()[][]"), true);
}

TEST_F(DiffPspTest, LongTest7) {
  ASSERT_EQ(earleyRecognize(*G, "(())][]{{{}}}{{(([[][]))}}{{(())}}{}{}()()()()[][]"), false);
}

TEST_F(DiffPspTest, LongTest8) {
  ASSERT_EQ(earleyRecognize(*G1, "(())[]]{{{}}}{{(([[[]]))}}{{(())}}{}{}()()()()[][]"), false);
}
