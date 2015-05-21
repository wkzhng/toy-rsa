#include "bigint.h"
#include "random.h"
#include <cstdint>
#include <cstring>
#include <cassert>

Random g_random;
const int kTestIteration = 1000;

void test_bigint_get_set() {
  const int kTestLength = 1024;
  printf("test_bigint_get_set: %d iteration, max length = %d\n",
         kTestIteration, kTestLength);

  for (int i = 0; i < kTestIteration; ++i) {
    size_t n = g_random.get<size_t>() % kTestLength + 1;
    char buf_in[n];
    g_random.get(buf_in, n);

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
  printf("test_bigint_plus: %d iteration\n", kTestIteration);

  for (int i = 0; i < kTestIteration; ++i) {
    uint32_t ia, ib;
    g_random.get(ia);
    g_random.get(ib);
    uint64_t iret = static_cast<uint64_t>(ia) + static_cast<uint64_t>(ib);

    BigInt ba = ia;
    BigInt bb = ib;
    BigInt bret = ba + bb;
    BigInt bconv = iret;

    assert(bret == bconv);
  }
}

void test_bigint_cmp() {
  printf("test_bigint_cmp: %d iteration\n", kTestIteration);

  for (int i = 0; i < kTestIteration; ++i) {
    uint64_t ia, ib;
    g_random.get(ia);
    g_random.get(ib);

    BigInt ba = ia;
    BigInt bb = ib;

    assert((ba < bb) == (ia < ib));
    assert((ba > bb) == (ia > ib));
    assert((ba == bb) == (ia == ib));
    assert((ba >= bb) == (ia >= ib));
    assert((ba <= bb) == (ia <= ib));
  }
}

void test_bigint_div_mult_2() {
  printf("test_bigint_div_2: %d iteration\n", kTestIteration);

  for (int i = 0; i < kTestIteration; ++i) {
    uint32_t rand_val;
    g_random.get(rand_val);

    BigInt test_val = rand_val;
    test_val.div_2();

    BigInt std_val = rand_val / 2;
    assert(std_val == test_val);

    std_val = static_cast<uint64_t>(rand_val) * 2;
    test_val = rand_val;
    test_val.mult_2();
    assert(std_val == test_val);
  }
}

void test_random() {
  constexpr int kNum = 10;
  printf("test_bigint_get_set: showing %d g_random bytes:\n", kNum);

  for (int i = 0; i < kNum; ++i) {
    unsigned char v;
    g_random.get(&v, sizeof(v));
    printf("%x ", v);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  test_bigint_div_mult_2();
  test_bigint_cmp();
  test_bigint_get_set();
  test_bigint_plus();
  return 0;
}
