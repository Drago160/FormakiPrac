#include "CF_Grammar.h"

std::string CF_Grammar::Parser::ExtractSegm(size_t left, size_t right) {
  std::string segm;
  segm.resize(right - left + 1);
  for (size_t i = left; i <= right; ++i) {
    segm[i - left] = input_[i];
  }
  return segm;
}

void CF_Grammar::Parser::ReadRule() {
  char src = input_[read_idx];
  read_idx += 3; // ignore(->)
  size_t begin = read_idx;
  while (input_[read_idx] != ';') {
    if (input_[read_idx] == '|') {
      InsertNewRightPart(src, ExtractSegm(begin, read_idx - 1));
      begin = read_idx + 1;
    }
    ++read_idx;
  }
  InsertNewRightPart(src, ExtractSegm(begin, read_idx - 1));
  if (input_.size() != read_idx) {
    if (input_[read_idx] == '\n') {
      ++read_idx;
    }
  }
  ++read_idx;
}

void CF_Grammar::Parser::InsertNewRightPart(char src, const std::string& dst) {
  if (grammar_ptr_->rules_.contains(src)) {
    grammar_ptr_->rules_[src].push_back(dst);
  } else {
    grammar_ptr_->rules_.insert({src, {dst}});
  }
}

void CF_Grammar::Parser::HandleNonAndTerminals() {
  for (char c : input_) {
    if (c == '-' || c == '\n' || c == '|' || c == '>' || c == ' ' || c == ';') {
      continue;
    }
    if (grammar_ptr_->rules_.contains(c)) {
      grammar_ptr_->non_terminals_.insert(c);
    } else {
      grammar_ptr_->terminals_.insert(c);
    }
  }
}

void CF_Grammar::Parser::ParseFormat() {
  grammar_ptr_->start_terminal_ = 'S';
  while (read_idx < input_.size() - 1) {
    ReadRule();
  }
  HandleNonAndTerminals();
}