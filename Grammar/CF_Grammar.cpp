#include "CF_Grammar.h"

std::unordered_map<char, std::vector<std::string>> CF_Grammar::GetRules() const {
  return rules_;
}

std::unordered_set<char> CF_Grammar::GetTerminals() const {
  return terminals_;      // Sigma
}

char CF_Grammar::GetStartNonTerm() const { return start_terminal_; }

CF_Grammar::CF_Grammar(const std::vector<char>& non_terminals,
                       const std::vector<char>& terminals,
                       const std::vector<std::vector<std::string>>& rules,
                       char S) {
  for (char c : non_terminals) {
    non_terminals_.insert(c);
  }
  for (char c : terminals) {
    terminals_.insert(c);
  }
  start_terminal_ = S;
  for (auto rule : rules) {
    char src = rule[0][0];
    rules_.insert({src, std::vector<std::string>(0)});
    for (std::vector<std::string>::iterator it = rule.begin() + 1; it != rule.end(); ++it) {
      rules_[src].push_back(*it);
    }
  }
}

CF_Grammar::CF_Grammar(std::unordered_set<char> non_termianls,
                       std::unordered_set<char> terminals,
                       std::unordered_map<char, std::vector<std::string>> rules,
                       char S) : rules_(rules), start_terminal_(S) {
  non_terminals_ = non_termianls;
  terminals_ = terminals;
}

std::string ExtractSegm(const std::string& str, size_t left, size_t right) {
  std::string segm;
  segm.resize(right - left + 1);
  for (size_t i = left; i <= right; ++i) {
    segm[i - left] = str[i];
  }
  return segm;
}
CF_Grammar::CF_Grammar(const std::string& rules) {
  CF_Creator builder(rules, this);
  builder.ParseFormat();
}

void CF_Grammar::PrintInfo() {
  std::cout << "Terminals_: ";
  for (const char c : terminals_) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
  std::cout << "non_terminals_: ";
  for (const char c : non_terminals_) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
  for (const auto& iter : rules_) {
    std::cout << iter.first << " --> ";
    for (const auto& item : iter.second) {
      std::cout << item << " | ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}