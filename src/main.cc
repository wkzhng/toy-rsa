#include "bigint.h"
#include "random.h"
#include <cstdint>
#include <cstring>
#include <cassert>

void test_bigint_get_set() {
  Random random(Random::kInsecure);

  const int kTestIteration = 1000;
  const int kTestLength = 1024;
  printf("test_bigint_get_set: %d iteration, max length = %d\n",
         kTestIteration, kTestLength);

  for (int i = 0; i < kTestIteration; ++i) {
    size_t n = random.get() % kTestLength + 1;
    char buf_in[n];
    random.get(buf_in, n);

    BigInt bi;
    bi.set_bytes(buf_in, n);

    size_t bi_n = bi.get_num_bytes();
    assert(bi_n <= n);

    char buf_out[n];
    bi.get_bytes(buf_out);
    assert(memcmp(buf_in, buf_out, bi_n) == 0);
  }
}

void test_bigint_plus() {
  const int kTestIteration = 1000;
  printf("test_bigint_plus: %d iteration", kTestIteration);

  Random random(Random::kInsecure);
  for (int i = 0; i < 1000; ++i) {
    uint16_t ia = random.get();
    uint16_t ib = random.get();
    uint64_t iret = ia + ib;

    BigInt ba = ia;
    BigInt bb = ib;
    BigInt bret = ba + bb;
    BigInt bconv = iret;

    assert(bret == bconv);
  }
}

void test_random() {
  constexpr int kNum = 10;
  printf("test_bigint_get_set: showing %d random bytes:\n", kNum);

  Random random;
  for (int i = 0; i < kNum; ++i) {
    unsigned char v;
    random.get(&v, sizeof(v));
    printf("%x ", v);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  test_bigint_get_set();
  test_bigint_plus();
  return 0;
}
