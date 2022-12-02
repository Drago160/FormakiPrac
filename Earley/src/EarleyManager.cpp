#include "EarleyManger.h"
bool EarleyManager::Situation::operator<(const EarleyManager::Situation& situation) const {

  if (src < situation.src) {
    return true;
  } else if (src > situation.src) {
    return false;
  }

  if (point_pos < situation.point_pos) {
    return true;
  } else if (point_pos > situation.point_pos) {
    return false;
  }

  if (word < situation.word) {
    return true;
  } else if (word > situation.word) {
    return false;
  }

  if (parent_pos < situation.parent_pos) {
    return true;
  } else if (parent_pos > situation.parent_pos) {
    return false;
  }
  return false;
}

bool EarleyManager::Situation::operator==(const EarleyManager::Situation& situation) const {
  return (point_pos == situation.point_pos &&
      word == situation.word &&
      parent_pos == situation.parent_pos &&
      src == situation.src);
}
EarleyManager::Backet::Backet(const Situation& sit) {
  pathes.insert({sit.AfterPointSymb(), {sit}});
}

const std::set<EarleyManager::Situation>& EarleyManager::Backet::GetIterPath( char letter) const {
  return pathes.at(letter);
}

void EarleyManager::Backet::Insert(const EarleyManager::Situation& situation) {
  if (pathes.contains(situation.AfterPointSymb())) {
    pathes.at(situation.AfterPointSymb()).insert(situation);
  } else {
    pathes.insert({situation.AfterPointSymb(), {situation}});
  }
}

bool EarleyManager::Backet::Contains(const EarleyManager::Situation& situation) const {
  if (pathes.contains(situation.AfterPointSymb())) {
    for (const auto& sit : pathes.at(situation.AfterPointSymb())) {
      if (situation == sit) {
        return true;
      }
    }
  }
  return false;
}

EarleyManager::EarleyManager(CF_Grammar& G): rules_(G.GetRules()), terminals_(G.GetTerminals()) {
  start_non_terminal_ = G.GetStartNonTerm();
  std::string start;
  start.push_back(start_non_terminal_);
  Situation zero_situation('0', start, 0, 0);  // S' := 0
  parse_list_.push_back(Backet(zero_situation));
}

bool EarleyManager::Recognize(const std::string& word) {
  this->word_ = word;
  changes_flag = true;
  while (changes_flag) {
    changes_flag = false;
    Complete(0);
    Predict(0);
  }
  for (size_t i = 1; i <= word.size(); ++i) {
    can_complete_situations_.clear();
    Scan(i - 1);
    changes_flag = true;
    while (changes_flag) {
      changes_flag = false;
      Complete(i);
      Predict(i);
    }
  }
  std::string start;
  start.push_back(start_non_terminal_);
  Situation end_expect_situation('0', start, 1, 0);
  return can_complete_situations_.contains(end_expect_situation);
}

bool EarleyManager::Situation::CanComplete() const {
  return word.size() == point_pos;
}

EarleyManager::Situation EarleyManager::Situation::ShiftCopy() const {
  Situation copy = *this;
  ++copy.point_pos;
  return copy;
}

void EarleyManager::Complete(size_t list_idx) {
  for (const Situation& complited : can_complete_situations_) { // перебираем ситуации с точкой в конце
    if (parse_list_[complited.parent_pos].pathes.contains(complited.src)) { // если есть возможности для Complete
      for (const Situation& to_complite : parse_list_[complited.parent_pos].GetIterPath(complited.src)) { // перебираем все которые можем комплитить
        Situation shifts = to_complite.ShiftCopy();
        if (shifts.CanComplete()) { //  Если можем продолжить новое правило
          if (!can_complete_situations_.contains(shifts)) {
            can_complete_situations_.insert(shifts);
            changes_flag = true;
          }
        } else {
          if (!parse_list_[list_idx].Contains(shifts)) {
            parse_list_[list_idx].Insert(shifts);
            changes_flag = true;
          }
        }
      }
    }
  }
}

bool EarleyManager::IsRuleNonTerminal(char c) const {
  return rules_.find(c) != rules_.end();
}

char EarleyManager::Situation::AfterPointSymb() const {
  return word[point_pos];
}

void EarleyManager::Predict(size_t list_idx) {
  for (const auto& rule : rules_) {  //  Перебираем правила грамматики A->...
    if (parse_list_[list_idx].pathes.contains(rule.first)) { // если в D_j где-то после точки есть A
      for (const std::string& path : rule.second) { //  перебираем правые части правил A->...
        Situation insert_situation(rule.first, path, 0, list_idx); // то что выводится predict'ом
        if (path == "") {
          if (!can_complete_situations_.contains(insert_situation)) { // если точка стоит в конце
            can_complete_situations_.insert(insert_situation);
            changes_flag = true;
          }
        } else {
          if (!parse_list_[list_idx].Contains(insert_situation)) { // если такого правила еще нету
            parse_list_[list_idx].Insert(insert_situation);
            changes_flag = true;
          }
        }
      }
    }
  }
}

void EarleyManager::Scan(size_t list_idx) {
  Backet new_backet;
  if (parse_list_[list_idx].pathes.contains(word_[list_idx])) { // если есть буква после нетерминала
    for (const Situation& sit : parse_list_[list_idx].GetIterPath(word_[list_idx])) { // итерируемся по ситуациям с точкой перед idx-й бувой
      Situation shifts = sit.ShiftCopy();
      if (shifts.CanComplete()) { // если точка в конце
        if (!can_complete_situations_.contains(shifts)) {
          can_complete_situations_.insert(shifts);
        }
      } else {
        if (!new_backet.Contains(shifts)) {
          new_backet.Insert(shifts);
        }
      }
    }
  }
  parse_list_.push_back(new_backet);
}