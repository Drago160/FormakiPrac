#include "earley.h"

bool earleyRecognize(const CF_Grammar& G, const std::string& word) {
  EarleyManager manger(G);
  return manger.Recognize(word);
}
