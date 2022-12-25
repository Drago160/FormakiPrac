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

  CF_Grammar() = default;

  CF_Grammar(const std::vector<char>& non_terminals,
             const std::vector<char>& terminals,
             const std::vector<std::vector<std::string>>& rules,
             char S);

  char GetStartNonTerm() const;

  std::unordered_map<char, std::vector<std::string>> GetRules() const;

  std::unordered_set<char> GetTerminals() const;

  void PrintInfo();

 private:

  class CF_Creator {
   public:
    CF_Creator(const std::string input, CF_Grammar* grammar_ptr)
        : input_(input), grammar_ptr_(grammar_ptr) {};
    void ParseFormat();
   private:
    void ReadRule();
    void InsertNewRightPart(char src, const std::string& dst);
    std::string ExtractSegm(size_t left, size_t right);
    void HandleNonAndTerminals();
    CF_Grammar* grammar_ptr_;
    std::string input_;
    size_t read_idx = 0;
  };

  std::unordered_set<char> terminals_;                          // Sigma
  std::unordered_set<char> non_terminals_;                       // N
  std::unordered_map<char, std::vector<std::string>> rules_;    // P
  char start_terminal_;                                          // S
};
