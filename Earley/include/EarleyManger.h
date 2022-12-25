#pragma once
#include "CF_Grammar.h"
#include <vector>
#include <set>

class EarleyManager {
 public:
  EarleyManager(const CF_Grammar& grammar);

  bool Recognize(const std::string& word);

 private:
  struct Situation {   //  [src -> w1w2, parent_pos], when |w1| = point_position
    char src;
    size_t point_position;
    std::string word;
    size_t parent_pos;
    Situation() = default;
    Situation(char src, std::string word, size_t point_position, size_t parent_pos)
        : src(src), word(word), point_position(point_position), parent_pos(parent_pos) {}

    bool operator<(const Situation& situation) const;

    bool operator==(const Situation& situation) const;

    bool CanComplete() const;

    Situation ShiftCopy() const;

    char AfterPointSymb() const;

  };

  struct Situation_hash {
    std::size_t operator()(Situation const& sit) const {
      return std::hash<std::string>()(sit.word) ^ sit.parent_pos ^ sit.point_position;
    }
  };

  struct Bucket {
    Bucket(const Situation&);

    Bucket() = default;

    std::unordered_map<char, std::set<Situation>> pathes;

    const std::set<Situation>& GetIterPath(char src) const;

    void Insert(const Situation& situation);

    bool Contains(const Situation& situation) const;
  };

 private:
  bool IsRuleNonTerminal(char c) const;

  void Complete(size_t list_idx);

  void Predict(size_t list_idx);

  void Scan(size_t list_idx);

  std::string word_;
  bool changes_flag;
  std::unordered_set<Situation, Situation_hash> can_complete_situations_;
  const std::unordered_map<char, std::vector<std::string>> rules_;
  std::vector<Bucket> parse_list_;
  std::unordered_set<char> terminals_;
  char start_non_terminal_;
};