#include "earley.h"

bool earleyRecognize(CF_Grammar G, std::string word) {
  EarleyManager manger(G);
  return manger.Recognize(word);
}
