#ifndef BIGINT_H_BM8XETKU
#define BIGINT_H_BM8XETKU
#include <cstdint>
#include <vector>
using namespace std;

class BigInt {
private:
  using Cell = uint8_t;
  using Cells = vector<Cell>;
  using BigCell = uint16_t;
  static constexpr size_t kCellBitsNum = sizeof(Cell) * 8;

  Cells cells_;

public:
  BigInt();
  BigInt(size_t integer);
  BigInt &operator=(size_t integer);

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
};

#endif /* end of include guard: BIGINT_H_BM8XETKU */
