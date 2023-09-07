#include "gtest/gtest.h"
#include "EarleyManager.h"
#include "earley.h"

class ManagerTester: public ::testing::Test  {
 public:

  bool IsBucketEquals(const EarleyManager::Bucket b1, const EarleyManager::Bucket b2) {
    return b1.pathes == b2.pathes;
  }

  bool IsEqualParseList(const std::vector<EarleyManager::Bucket>& pl1,
                        const std::vector<EarleyManager::Bucket>& pl2) {
    if (pl1.size() != pl2.size()) {
      return false;
    }
    for (const auto& elem1 : pl1) {
      bool existst = false;
      for (const auto& elem2 : pl2) {
        if (IsBucketEquals(elem1, elem2)) {
          existst = true;
        }
      }
      if (!existst) {
        return false;
      }
    }
    return true;
  }

  bool CheckConstruct() {
    if (M->word_ != "aabb") {
      return false;
    }
    if (M->start_non_terminal_ != 'S') {
      return false;
    }
    std::unordered_set<char> expected_terminals = {'a', 'b'};
    if (M->terminals_ != expected_terminals) {
      return false;
    }
    std::unordered_map<char, std::vector<std::string>> expected_rules;
    expected_rules['S'] = {"aFbF"};
    expected_rules['F'] = {"aFb", ""};
    if (M->rules_ != expected_rules) {
      return false;
    }
    if (!M->can_complete_situations_.empty()) {
      return false;
    }
    std::vector<EarleyManager::Bucket> expected_parse_list;
    EarleyManager::Situation expected_first_situation('0', "S", 0, 0);
    expected_parse_list.push_back(EarleyManager::Bucket(expected_first_situation));
    if (!IsEqualParseList(expected_parse_list, M->parse_list_)) {
      return false;
    }

    return true;
  }

  bool CheckFirstComplite() {
    M->Complete(0);
    if (!M->can_complete_situations_.empty()) {
      return false;
    }
    std::vector<EarleyManager::Bucket> expected_parse_list;
    EarleyManager::Situation expected_first_situation('0', "S", 0, 0);
    expected_parse_list.push_back(EarleyManager::Bucket(expected_first_situation));
    if (!M->can_complete_situations_.empty()) {
      return false;
    }
    if (!IsEqualParseList(expected_parse_list, M->parse_list_)) {
      return false;
    }
    return true;
  }

  bool CheckFirstPredict() {
    M->Predict(0);
    std::vector<EarleyManager::Bucket> expected_parse_list;
    EarleyManager::Situation first_situation('0', "S", 0, 0);
    expected_parse_list.push_back(EarleyManager::Bucket(first_situation));
    expected_parse_list[0].Insert({'S', "aFbF", 0, 0});
    if (!M->can_complete_situations_.empty()) {
      return false;
    }
    if (!IsEqualParseList(expected_parse_list, M->parse_list_)) {
      return false;
    }
    return true;
  }

  bool CheckScan() {
    M->parse_list_[0].Insert({'S', "aFbF", 0, 0});
    std::vector<EarleyManager::Bucket> expected_parse_list = M->parse_list_;
    M->Scan(0);
    expected_parse_list.push_back(EarleyManager::Bucket({'S', "aFbF", 1, 0}));
    if (!M->can_complete_situations_.empty()) {
      return false;
    }
    if (!IsEqualParseList(expected_parse_list, M->parse_list_)) {
      return false;
    }
    return true;
  }

  bool CheckPredict() {
    M->parse_list_[0].Insert({'S', "aFbF", 0, 0});
    M->parse_list_.push_back(EarleyManager::Bucket({'S', "aFbF", 1, 0}));
    std::vector<EarleyManager::Bucket> expected_parse_list = M->parse_list_;
    M->Predict(1);
    expected_parse_list[1].Insert({'F', "aFb", 0, 1});
    std::unordered_set<EarleyManager::Situation, EarleyManager::Situation_hash> expected_can_complite;
    expected_can_complite.insert({'F', "", 0, 1});
    if (!IsEqualParseList(M->parse_list_, expected_parse_list)) {
      return false;
    }
    if (expected_can_complite != M->can_complete_situations_) {
      return false;
    }
    return true;
  }

  bool CheckComplite() {
    M->parse_list_[0].Insert({'S', "aFbF", 0, 0});
    M->parse_list_.push_back(EarleyManager::Bucket({'S', "aFbF", 1, 0}));
    M->parse_list_[1].Insert({'F', "aFb", 0, 1});
    M->can_complete_situations_.insert({'F', "", 0, 1});
    std::vector<EarleyManager::Bucket> expected_parse_list = M->parse_list_;
    std::unordered_set<EarleyManager::Situation, EarleyManager::Situation_hash> expected_can_complite = M->can_complete_situations_;
    M->Complete(1);
    expected_parse_list[1].Insert({'S', "aFbF", 2, 0});
    if (!IsEqualParseList(M->parse_list_, expected_parse_list)) {
      return false;
    }
    if (expected_can_complite != M->can_complete_situations_) {
      return false;
    }
    return true;
  }

 protected:
  void SetUp() {
    M = new EarleyManager(CF_Grammar("S->aFbF;F->aFb|;"));
    M->word_ = "aabb";
  }
  void TearDown() {
    delete M;
  }
  EarleyManager* M;
};

TEST_F(ManagerTester, ConstructTest) {
  ASSERT_TRUE(CheckConstruct());
}

TEST_F(ManagerTester, Complite0) {
  ASSERT_TRUE(CheckFirstComplite());
}

TEST_F(ManagerTester, Predict0) {
  ASSERT_TRUE(CheckFirstPredict());
}

TEST_F(ManagerTester, Scan) {
  ASSERT_TRUE(CheckScan());
}

TEST_F(ManagerTester, Predict) {
  ASSERT_TRUE(CheckPredict());
}

TEST_F(ManagerTester, Complite) {
  ASSERT_TRUE(CheckComplite());
}