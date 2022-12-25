#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

class CF_Grammar {
 public:
  CF_Grammar(std::unordered_set<char> non_termianls,  //  <N, Sigma, P, S>
             std::unordered_set<char> terminals,
             std::unordered_map<char, std::vector<std::string>> rules,
             char S = 'S');

  CF_Grammar(const std::string& rules); //  Input in format: A->str1|str2|...|strn;B->....

  CF_Grammar(const std::vector<char>& non_terminals,
             const std::vector<char>& terminals,
             const std::vector<std::vector<std::string>>& rules,
             char S);

  char GetStartNonTerm() const;

  std::unordered_map<char, std::vector<std::string>> GetRules() const;

  std::unordered_set<char> GetTerminals() const;

  void PrintInfo();

 private:
  std::unordered_set<char> terminals_;                          // Sigma
  std::unordered_set<char> non_terminals_;                       // N
  std::unordered_map<char, std::vector<std::string>> rules_;    // P
  char start_terminal_;                                          // S
};
