#include "CF_Grammar.h"
#include "earley.h"

int main() {
  CF_Grammar G("S->aA|Aa|A;A->aA|a;");
  return 0;
}
