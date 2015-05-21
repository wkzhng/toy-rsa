#ifndef BIGINT_H_BM8XETKU
#define BIGINT_H_BM8XETKU
#include <cstdint>
#include <vector>
using namespace std;

class BigInt {
private:
  using Cell = uint8_t;
  using BigCell = uint16_t;
  using Cells = vector<Cell>;
  static constexpr size_t kCellBitsNum = sizeof(Cell) * 8;

  Cells cells_;

public:
  BigInt();
  template<typename T> inline BigInt(T integer);
  template<typename T> inline BigInt &operator=(T integer);

  int compare(const BigInt& op) const;
  bool operator==(const BigInt& op) const;
  bool operator<(const BigInt& op) const;
  bool operator<=(const BigInt& op) const;
  bool operator>(const BigInt& op) const;
  bool operator>=(const BigInt& op) const;

  BigInt operator+(const BigInt &op) const;
  BigInt &operator+=(const BigInt &op);

  void set_bytes(void *buffer, size_t size);
  void get_bytes(void *buffer) const;
  size_t get_num_bits() const;
  size_t get_num_bytes() const;

  void div_2();
};

template<typename T> BigInt::BigInt(T integer) {
  *this = integer;
}

template<typename T> BigInt &BigInt::operator=(T integer) {
  set_bytes(&integer, sizeof(T));
  return *this;
}

#endif /* end of include guard: BIGINT_H_BM8XETKU */
