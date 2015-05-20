#include "bigint.h"
#include "random.h"
#include <cstdint>

void test_random() {
  constexpr int kNum = 10;
  Random random;
  for (int i = 0; i < kNum; ++i) {
    unsigned char v;
    random.get(&v, sizeof(v));
    printf("%x ", v);
  }
}

int main(int argc, char *argv[])
{
  test_random();
  return 0;
}
