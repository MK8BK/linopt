#include <istream>
#include <ostream>
#include <stdexcept>

namespace linopt::inmemory {

template <typename E> int Matrix<E>::getN() const { return data.size(); }

template <typename E> int Matrix<E>::getM() const {
  if (getN() == 0)
    throw std::runtime_error("Invalid matrix dimension (<1).");
  return data[0].size();
}
template <typename E>
Matrix<E>::Matrix(int n, int m) : data(n, std::vector<E>(m, E())) {
  if (n < 1 || m < 1)
    throw std::runtime_error("Invalid matrix dimension (<1).");
}
template <typename E>
Matrix<E>::Matrix(int n, int m, E e) : data(n, std::vector<E>(m, E(e))) {
  if (n < 1 || m < 1)
    throw std::runtime_error("Invalid matrix dimension (<1).");
}

template <typename E>
Matrix<E>::Matrix(std::initializer_list<std::initializer_list<E>> il) {
  if (il.size() < 1 || il.begin()->size() < 1)
    throw std::runtime_error(
        "Invalid matrix dimension (<1) in initializer_list<E>.");
  size_t m = il.begin()->size();
  for (const std::initializer_list<E> &row : il) {
    if (row.size() != m)
      throw std::runtime_error(
          "Jagged initializer_list not allowed for matrix initialization.");
    data.push_back(row);
  }
}

// copy constructor
template <typename E>
Matrix<E>::Matrix(const Matrix<E> &src) : data(src.data) {}

// move constructor
template <typename E> Matrix<E>::Matrix(Matrix<E> &&src) {
  data.swap(src.data);
}

// copy assignment operator
template <typename E> Matrix<E> &Matrix<E>::operator=(const Matrix<E> &other) {
  data = other.data; // expensive copy
  return *this;
}

// move assignment operator
template <typename E> Matrix<E> &Matrix<E>::operator=(Matrix<E> &&other) {
  data.swap(other.data); // inexpensive, constant time exchange
  return *this;
}

// constant time swap
template <typename E> void Matrix<E>::swap(Matrix<E> &other) {
  data.swap(other.data);
}

template <typename E> const E &Matrix<E>::get(int r, int c) const {
  if (r >= getN() || r < 0 || c < 0 || c >= getM())
    throw std::runtime_error("Invalid index pair.");
  return data[r][c];
}
template <typename E> E &Matrix<E>::get(int r, int c) {
  if (r >= getN() || r < 0 || c < 0 || c >= getM())
    throw std::runtime_error("Invalid index pair.");
  return data[r][c];
}

template <typename E>
Matrix<E> Matrix<E>::operator+(const Matrix<E> &other) const {
  if (getN() != other.getN() || getM() != other.getM())
    throw std::runtime_error("Invalid dimensions for matrix addition.");
  Matrix<E> r(getN(), getM());
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < getM(); j++)
      r.get(i, j) = data[i][j] + other.get(i, j);
  return r;
}

template <typename E>
Matrix<E> Matrix<E>::operator-(const Matrix<E> &other) const {
  if (getN() != other.getN() || getM() != other.getM())
    throw std::runtime_error("Invalid dimensions for matrix subtraction.");
  Matrix<E> r(getN(), getM());
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < getM(); j++)
      r.get(i, j) = data[i][j] - other.get(i, j);
  return r;
}

template <typename E>
Matrix<E> Matrix<E>::operator*(const Matrix<E> &other) const {
  if (getM() != other.getN())
    throw std::runtime_error("Invalid dimensions for matrix multiplication.");
  Matrix<E> r(getN(), other.getM());
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < other.getM(); j++)
      for (int k = 0; k < getM(); k++)
        r.get(i, j) += data[i][k] * other.get(k, j);
  return r;
}

template <typename E> Matrix<E> &Matrix<E>::operator+=(const Matrix<E> &other) {
  *this = *this + other;
  return *this;
}

template <typename E> Matrix<E> &Matrix<E>::operator-=(const Matrix<E> &other) {
  *this = *this - other;
  return *this;
}

template <typename E> Matrix<E> &Matrix<E>::operator*=(const Matrix<E> &other) {
  *this = *this * other;
  return *this;
}

template <typename E> bool Matrix<E>::operator==(const Matrix<E> &other) const {
  if (getN() != other.getN() || getM() != other.getM())
    return false;
  // hopefully not too expensive
  return data == other.data;
}

template <typename E> bool Matrix<E>::operator!=(const Matrix<E> &other) const {
  return !(*this == other);
}

template <typename E> Matrix<E> &Matrix<E>::fill(E e) {
  for (std::vector<E> &row : data)
    std::fill(row.begin(), row.end(), e);
  return *this;
}

template <typename E>
template <typename S>
Matrix<E> Matrix<E>::operator*(const S &s) const {
  Matrix<E> r(getN(), getM());
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < getM(); j++)
      r.get(i, j) = s * data[i][j];
  return r;
}

template <typename E>
template <typename S>
Matrix<E> &Matrix<E>::operator*=(const S &s) {
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < getM(); j++)
      data[i][j] *= s;
  return *this;
}

template <typename E> Matrix<E> &Matrix<E>::inplaceTranspose() {
  if (getM() == getN()) {
    // do it in place
    for (int i = 0; i < getN(); i++)
      for (int j = i; j < getM(); j++)
        std::swap(data[i][j], data[j][i]);
  } else {
    *this = this->transpose();
  }
  return *this;
}

template <typename E> Matrix<E> Matrix<E>::transpose() const {
  Matrix<E> r(getM(), getN());
  for (int i = 0; i < getN(); i++)
    for (int j = 0; j < getM(); j++)
      r.get(j, i) = data[i][j];
  return r;
}

template <typename E>
template <typename S>
Matrix<E> &Matrix<E>::combineRows(int row1, S factor1, int row2, S factor2,
                                  int destinationRow) {
  if (row1 < 0 || row1 >= getN() || row2 < 0 || row2 >= getM())
    throw std::runtime_error("Invalid row combination: bad index.");
  for (int j = 0; j < getM(); j++)
    data[destinationRow][j] = factor1 * data[row1][j] + factor2 * data[row2][j];
  return *this;
}
template <typename E>
Matrix<E> &Matrix<E>::combineColumns(int column1, int factor1, int column2,
                                     int factor2, int destinationColumn) {
  if (column1 < 0 || column1 >= getM() || column2 < 0 || column2 >= getM())
    throw std::runtime_error("Invalid column combination: bad index.");
  for (int i = 0; i < getN(); i++)
    data[i][destinationColumn] =
        factor1 * data[i][column1] + factor2 * data[i][column2];
  return *this;
}

template <typename E>
template <typename S>
Matrix<E> &Matrix<E>::multiplyRow(int row, S s) {
  if (row < 0 || row >= getN())
    throw std::runtime_error("Invalid row multiplication: bad index.");
  for (int j = 0; j < getM(); j++)
    data[row][j] *= s;
  return *this;
}

template <typename E>
template <typename S>
Matrix<E> &Matrix<E>::multiplyColumn(int column, S s) {
  if (column < 0 || column >= getM())
    throw std::runtime_error("Invalid column multiplication: bad index.");
  for (int i = 0; i < getN(); i++)
    data[i][column] *= s;
  return *this;
}

template <typename E>
std::ostream &operator<<(std::ostream &os, const Matrix<E> &matrix) {
  os << matrix.getN() << ' ' << matrix.getM() << ' ';
  for (int i = 0; i < matrix.getN(); i++)
    for (int j = 0; j < matrix.getM(); j++)
      os << matrix.data[i][j] << ' ';
  return os;
}

template <typename E>
std::istream &operator>>(std::istream &is, Matrix<E> &matrix) {
  int n = 0, m = 0;
  is >> n >> m;
  matrix.data = std::vector<std::vector<E>>(n, std::vector<int>(m, E()));
  for (int i = 0; i < matrix.getN(); i++)
    for (int j = 0; j < matrix.getM(); j++)
      is >> matrix.data[i][j];
  return is;
}

template <typename E> Matrix<E> &Matrix<E>::fillRow(int row, E e) {
  if (row < 0 || row >= getN())
    throw std::runtime_error("Invalid row fill: bad index.");
  std::fill(data[row].begin(), data[row].end(), e);
  return *this;
}

template <typename E> Matrix<E> &Matrix<E>::fillColumn(int column, E e) {
  if (column < 0 || column >= getM())
    throw std::runtime_error("Invalid column fill: bad index.");
  for (int i = 0; i < getN(); i++)
    data[i][column] = E(e);
  return *this;
}

// std::ostream& operator<<(std::ostream& os) const;
} // namespace linopt::inmemory
