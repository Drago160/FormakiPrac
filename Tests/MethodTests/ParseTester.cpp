#include "CF_Grammar.h"
#include "gtest/gtest.h"

class ParseTester {
 public:
  static bool CheckPspBuild() {
    CF_Grammar G1("S->(S)S|;");
    if (G1.start_terminal_ != 'S') {
      return false;
    }
    std::unordered_set<char> expected_terminals = {')', '('};
    if (G1.terminals_ != expected_terminals) {
      return false;
    }
    std::unordered_set<char> expected_nonterminals = {'S'};
    if (G1.non_terminals_ != expected_nonterminals) {
      return false;
    }
    std::unordered_map<char, std::vector<std::string>> expected_rules;
    expected_rules['S'] = {"(S)S", ""};
    if (G1.rules_ != expected_rules) {
      return false;
    }
    return true;
  }

  static bool CheckBalansedBuild() {
    CF_Grammar G2("S->aA|bB|;A->aAA|bS|a;B->bBB|aS|b;");

    if (G2.start_terminal_ != 'S') {
      return false;
    }

    std::unordered_set<char> expected_terminals = {'a', 'b'};
    if (G2.terminals_ != expected_terminals) {
      return false;
    }
    std::unordered_set<char> expected_nonterminals = {'S', 'A', 'B'};
    if (G2.non_terminals_ != expected_nonterminals) {
      return false;
    }
    std::unordered_map<char, std::vector<std::string>> expected_rules;
    expected_rules['S'] = {"aA", "bB", ""};
    expected_rules['A'] = {"aAA", "bS", "a"};
    expected_rules['B'] = {"bBB", "aS", "b"};
    if (G2.rules_ != expected_rules) {
      return false;
    }
    return true;
  }

  static bool CheckFromHWBuild() {
    CF_Grammar G3({'T', 'A', 'B', 'C', 'K', 'R'},
    { 'a', 'b' },
    {
      { "T", "aA", "bB" },
      { "A", "aC", "bT" },
      { "B", "aT", "bK" },
      { "K", "aB" },
      { "C", "bA", "aR", "" },
      { "R", "aRR", "bC" }
    }, 'T');

    if (G3.start_terminal_ != 'T') {
      return false;
    }

    std::unordered_set<char> expected_terminals = {'a', 'b'};
    if (G3.terminals_ != expected_terminals) {
      return false;
    }
    std::unordered_set<char> expected_nonterminals = {'T', 'A', 'B', 'C', 'K', 'R'};
    if (G3.non_terminals_ != expected_nonterminals) {
      return false;
    }
    std::unordered_map<char, std::vector<std::string>> expected_rules;
    expected_rules['T'] = {"aA", "bB"};
    expected_rules['A'] = {"aC", "bT"};
    expected_rules['B'] = {"aT", "bK"};
    expected_rules['K'] = {"aB"};
    expected_rules['C'] = {"bA", "aR", ""};
    expected_rules['R'] = {"aRR", "bC"};
    if (G3.rules_ != expected_rules) {
      return false;
    }
    return true;
  }

};

TEST(ParseTester, pspBuildTest) {
  EXPECT_TRUE(ParseTester::CheckPspBuild());
}

TEST(ParseTester, BalancedBuildTest) {
  EXPECT_TRUE(ParseTester::CheckBalansedBuild());
}

TEST(ParseTester, FromHWBuildTest) {
  EXPECT_TRUE(ParseTester::CheckFromHWBuild());
}