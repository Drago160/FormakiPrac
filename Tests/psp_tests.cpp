#include "gtest/gtest.h"
#include "earley.h"

class PspTest : public ::testing::Test {
 protected:
  void SetUp() {
    G = new CF_Grammar("S->(S)S|;");
    G1 = new CF_Grammar("S->(F)F|;F->(F)F|");
  }
  CF_Grammar* G;
  CF_Grammar* G1;
};

TEST_F(PspTest, BasicTest1) {
  ASSERT_EQ(earleyRecognize(*G, "()"), true);
}

TEST_F(PspTest, BasicTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "()"), true);
}

TEST_F(PspTest, TestEmpty1) {
  ASSERT_EQ(earleyRecognize(*G, ""), true);
}

TEST_F(PspTest, TestEmpty2) {
  ASSERT_EQ(earleyRecognize(*G1, ""), true);
}

TEST_F(PspTest, MediumTest1) {
  ASSERT_EQ(earleyRecognize(*G, "(()())()()((())())"), true);
}

TEST_F(PspTest, MediumTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "(((()()()(()))()))"), true);
}

TEST_F(PspTest, LongTest1) {
  ASSERT_EQ(earleyRecognize(*G, "()()()(())()()()()((()))()()()()((()))((()))(())()()"), true);
}

TEST_F(PspTest, LongTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "()()()(())()()()()((()))()()()()((()))((()))(())()()"), true);
}

TEST_F(PspTest, LongRandomStressTests) {
  //  Generate psp with size near 1000
  const size_t iter_nums = 20;
  const size_t min_size = 1000;
  std::string str;
  for (size_t i = 0; i < iter_nums; ++i) {
    size_t breacket_res = 0;
    str = "";
    while (str.size() < min_size) {
      if (breacket_res == 0) {
        str.push_back('(');
        ++breacket_res;
      }
      if (rand() % 2 == 0) {
        str.push_back('(');
        ++breacket_res;
      } else {
        str.push_back(')');
        --breacket_res;
      }
    }
    while (breacket_res != 0) {
      str.push_back(')');
      breacket_res--;
    }

    ASSERT_EQ(earleyRecognize(*G, str), true);
    ASSERT_EQ(earleyRecognize(*G1, str), true);
  }

}

TEST_F(PspTest, OneBreacketTest1) {
  ASSERT_EQ(earleyRecognize(*G, "("), false);
}

TEST_F(PspTest, OneBreacketTest2) {
  ASSERT_EQ(earleyRecognize(*G1, "("), false);
}

TEST_F(PspTest, MediumTest3) {
  ASSERT_EQ(earleyRecognize(*G, "())((()((())))((()()("), false);
}

TEST_F(PspTest, MediumTest4) {
  ASSERT_EQ(earleyRecognize(*G1, "())((()((())))((()()("), false);
}

TEST_F(PspTest, MediumTest5) {
  ASSERT_EQ(earleyRecognize(*G, "()(()))((()()(()"), false);
}

TEST_F(PspTest, MediumTest6) {
  ASSERT_EQ(earleyRecognize(*G1, "()(()))((()()(()"), false);
}

TEST_F(PspTest, StartTest1) {
  ASSERT_EQ(earleyRecognize(*G, ")(()()()"), false);
}

TEST_F(PspTest, StartTest2) {
  ASSERT_EQ(earleyRecognize(*G1, ")(()()()"), false);
}

TEST_F(PspTest, MediumTest7) {
  ASSERT_EQ(earleyRecognize(*G, "()(())(()))(()()"), false);
}

TEST_F(PspTest, MediumTest8) {
  ASSERT_EQ(earleyRecognize(*G1, "()(())(()))(()()"), false);
}