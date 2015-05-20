#ifndef RANDOM_H_4RZBVTGQ
#define RANDOM_H_4RZBVTGQ
#include <cstdio>

class Random {
private:
  FILE *rand_file_;

public:
  enum Mode {
    kInsecure = 0,
    kSecure = 1,
  };

  Random(Mode mode = kInsecure);
  ~Random();

  size_t get();
  bool get(void *buffer, size_t length);
};

#endif /* end of include guard: RANDOM_H_4RZBVTGQ */
