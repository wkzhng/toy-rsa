#include "bigint.h"
#include <algorithm>

BigInt::BigInt() {
}

BigInt::BigInt(size_t integer) {
  *this = integer;
}

BigInt &BigInt::operator=(size_t integer) {
  set_bytes(&integer, sizeof(size_t));
  return *this;
}

int BigInt::compare(const BigInt& op) const {
  if (this->cells_.size() < op.cells_.size()) return -1;
  if (this->cells_.size() > op.cells_.size()) return +1;

  auto pthis = cells_.crbegin();
  auto pthat = op.cells_.crbegin();
  for (;pthis != cells_.rend(); ++pthis, ++pthat) {
    if (*pthis < *pthat) return -1;
    if (*pthis > *pthat) return +1;
  }

  return 0;
}

bool BigInt::operator==(const BigInt& op) const {
  return compare(op) == 0;
}

bool BigInt::operator<(const BigInt& op) const {
  return compare(op) < 0;
}

bool BigInt::operator>(const BigInt& op) const {
  return compare(op) > 0;
}

bool BigInt::operator<=(const BigInt& op) const {
  return compare(op) <= 0;
}

bool BigInt::operator>=(const BigInt& op) const {
  return compare(op) >= 0;
}

BigInt BigInt::operator+(const BigInt &op) const {
  BigInt ret = *this;
  ret += op;
  return ret;
}

BigInt &BigInt::operator+=(const BigInt &op) {
  if (op.cells_.size() == 0) return *this;

  auto min_new_size = max(cells_.size(), op.cells_.size());
  cells_.reserve(min_new_size + 1); // max new size: have a carry bit
  cells_.resize(min_new_size);

  BigCell carry = 0;
  auto src = op.cells_.cbegin();
  auto dst = cells_.begin();

  for (; dst != cells_.end(); ++dst) {
    Cell src_val = src == op.cells_.end() ? 0 : *(src++);
    carry = src_val + *dst + carry;
    *dst = static_cast<Cell>(carry);
    carry >>= kCellBitsNum;
  }

  if (carry) cells_.push_back(static_cast<Cell>(carry));

  return *this;
}

size_t BigInt::get_num_bits() const {
  if (cells_.size() == 0) return 0;

  Cell last = cells_.back();
  Cell mask = 1 << (kCellBitsNum - 1);
  int remain = kCellBitsNum;
  for (remain = kCellBitsNum; !(mask & last); mask >>=1, --remain);

  return (cells_.size() - 1) * kCellBitsNum + remain;
}

size_t BigInt::get_num_bytes() const {
  size_t bits = get_num_bits();
  size_t bytes = bits / 8;
  return bits == bytes * 8 ? bytes : bytes + 1;
}

void BigInt::get_bytes(void *buffer) const {
  if (cells_.size() == 0) return;

  auto buf = reinterpret_cast<uint8_t *>(buffer);
  auto last = cells_.end(); --last;

  for (auto i = cells_.begin(); i != last; ++i) {
    auto tmp = *i;
    for (size_t j = 0; j < sizeof(Cell); ++j) {
      *(buf++) = static_cast<uint8_t>(tmp);
      tmp >>= 8;
    }
  }

  for (auto tmp = *last; tmp; tmp >>= 8) {
      *(buf++) = static_cast<uint8_t>(tmp);
  }
}

void BigInt::set_bytes(void *buffer, size_t size) {
  if (size == 0) return;

  // find the highest non-zero byte to adjust size
  auto buf_begin = reinterpret_cast<uint8_t *>(buffer);
  auto buf_end = buf_begin + size - 1;
  for (; buf_end != buf_begin && !*buf_end; --buf_end);
  size = buf_end - buf_begin + 1;

  cells_.clear();
  if (buf_end == buf_begin && !*buf_end) return; // no non-zero bytes

  // fill cells_
  size_t cells_num = size / sizeof(Cell);
  cells_.reserve(cells_num + 1);
  for (size_t i = 0; i < cells_num; ++i) {
    Cell cell_val = 0;
    for (size_t j = 0; j < sizeof(Cell); j++) {
      cell_val >>= 8;
      cell_val |= *(buf_begin++) << (kCellBitsNum - 8);
    }
    cells_.push_back(cell_val);
  }

  // if there are remaining bytes, fill them
  size_t remain = size - cells_num * sizeof(Cell);
  Cell cell_val = 0;
  for (size_t j = 0; j < sizeof(Cell); j++) {
    cell_val >>= 8;
    if (j < remain) cell_val |= *(buf_begin++) << (kCellBitsNum - 8);
  }

  if (remain != 0) cells_.push_back(cell_val);
}
