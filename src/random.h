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

  template<typename T> inline bool get(T &val);
  template<typename T> T get();
  bool get(void *buffer, size_t length);
};

template<typename T> inline bool Random::get(T &val) {
  return get(&val, sizeof(val));
}

template<typename T> T Random::get() {
  T val;
  get(&val, sizeof(val));
  return val;
}

#endif /* end of include guard: RANDOM_H_4RZBVTGQ */
