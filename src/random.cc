#include "random.h"

Random::Random(Mode mode) {
  rand_file_ = fopen(mode == kSecure ? "/dev/random" : "/dev/urandom", "rb");
}

Random::~Random() {
  if (rand_file_) fclose(rand_file_);
}

bool Random::get(void *buffer, size_t length) {
  size_t bytes_read = fread(buffer, length, 1, rand_file_);
  return bytes_read == length;
}

