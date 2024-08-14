/**
 * \file Matrix.h
 * \author mk8bk
 * \date 14/08/2024
 * \brief Declares the \sa linopt::inmemory::Matrix<E> class.
 * \details
 *  This class models an in-memory dense matrix. It provides an
 *  easy to use api. It provides methods to access and modify the
 *  matrix entries.
 */
#ifndef LINOPT_ERC_INMEMORY_MATRIX_MATRIX_H
#define LINOPT_ERC_INMEMORY_MATRIX_MATRIX_H

#include <ostream>
#include <vector>

namespace linopt::inmemory {
/**
 * \brief The Matrix<E> class stores nxm entries of type E.
 *
 * This class handles dense matrices.
 * The type E must model a commutative ring, that is: for e1, e2 of type E,
 * e1 * e2, e1+e2 must be well defined and of type E.
 *
 */
template <typename E = double> class Matrix {
private:
  /**
   * \brief The undelying matrix entries are stored in an stl vector
   * of vectors. It is never jagged *ie:* each vector row has the same size.
   */
  std::vector<std::vector<E>> data;

public:
  /**
   * \brief Get the number of rows in the matrix.
   * \return n: the number of rows in the matrix.
   */
  int getN() const;

  /**
   * \brief Get the number of columns in the matrix.
   * \return m: the number of columns in the matrix.
   */
  int getM() const;

  /**
   * \brief constructs an nxm matrix.
   *
   * Pre-filled with E().
   * \param n: number of rows in the matrix.
   * \param m: number of columns in the matrix.
   */
  Matrix(int n, int m);

  /**
   * \brief constructs an nxm matrix.
   *
   * Pre-filled with E(e).
   * \param e: default element copied in each entry.
   * \param n: number of rows in the matrix.
   * \param m: number of columns in the matrix.
   */
  Matrix(int n, int m, E e);

  /**
   * \brief Copy constructor.
   * \param src: the matrix to be copied.
   */
  Matrix(const Matrix<E> &src);

  /**
   * \brief Move constructor.
   * \param src: the r-value matrix to be moved.
   */
  Matrix(Matrix<E> &&src);

  /**
   * \brief Move constructor.
   * \param il: the initializer_list to be used for ... initializing the matrix.
   *     It must not be jagged: each row must have the same length.
   */
  Matrix(std::initializer_list<std::initializer_list<E>> il);

  /**
   * \brief Copy assignment operator.
   * \param src: the matrix to be copied.
   * \return a reference to the matrix after assignment.
   */
  Matrix<E> &operator=(const Matrix<E> &other);

  /**
   * \brief Move assignment operator.
   * \param src: the r-value matrix to be moved.
   * \return a reference to the matrix after assignment.
   */
  Matrix<E> &operator=(Matrix<E> &&other);

  /**
   * \brief Swap matrices. Constant time.
   * \param other: the matrix to swap with this matrix.
   * \return a reference to the matrix after the swap.
   */
  void swap(Matrix<E> &other);

  /**
   * \brief Matrix entry getter.
   *
   * Does bounds-checking.
   * \param r: the row index (starting at 0).
   * \param c: the column index (starting at 0).
   * \return constant reference to entry at position (r,c).
   */
  const E &get(int r, int c) const;

  /**
   * \brief Matrix entry setter/getter.
   *
   * Does bounds-checking.
   * \param r: the row index (starting at 0).
   * \param c: the column index (starting at 0).
   * \return reference to entry at position (r,c).
   */
  E &get(int r, int c);

  /**
   * \brief Transposes the matrix in-place.
   * \return reference to this matrix after the transposition is performed.
   */
  Matrix<E> &inplaceTranspose();

  /**
   * \brief Performs the transpose operation.
   * \return the transpose matrix.
   */
  Matrix<E> transpose() const;

  /**
   * \brief Performs the operation: destinationRow=row1*factor1 + row2*factor2.
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * Does bounds-checking.
   *
   * \param row1: index of row1.
   * \param factor1: scalar to multiply by row1.
   * \param row2: index of row2.
   * \param factor2: scalar to multiply by row2.
   * \param destinationRow: row position to be overwritten.
   * \return a reference to the matrix after the operation is performed.
   */
  template <typename S>
  Matrix<E> &combineRows(int row1, S factor1, int row2, S factor2,
                         int destinationRow);

  /**
   * \brief Performs the operation: destinationColumn=column1*factor1 + column2*factor2.
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * Does bounds-checking.
   *
   * \param column1: index of column1.
   * \param factor1: scalar to multiply by column1.
   * \param column2: index of column2.
   * \param factor2: scalar to multiply by column2.
   * \param destinationColumn: column position to be overwritten.
   * \return a reference to the matrix after the operation is performed.
   */
  Matrix<E> &combineColumns(int column1, int factor1, int column2, int factor2,
                            int destinationColumn);

  /**
   * \brief Performs the operation: row = row*s.
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * Does bounds-checking.
   *
   * \param row: index of row to be multiplied.
   * \param s: scalar to multiply by row.
   * \return a reference to the matrix after the operation is performed.
   */
  template <typename S> Matrix<E> &multiplyRow(int row, S s);

  /**
   * \brief Performs the operation: column = column*s.
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * Does bounds-checking.
   *
   * \param column: index of column to be multiplied.
   * \param s: scalar to multiply by row.
   * \return reference to the matrix after the operation is performed.
   */
  template <typename S> Matrix<E> &multiplyColumn(int column, S s);

  /**
   * \brief Sums two matrices with matching dimensions.
   *
   * If the dimensions don't match, a runtime_error is thrown.
   *
   * \param other: reference to the matrix to be added to produce the return matrix.
   * \return the sum of the two matrices.
   */
  Matrix<E> operator+(const Matrix<E> &other) const;

  /**
   * \brief Subtracts matrix other from this matrix.
   *
   * If the dimensions don't match, a runtime_error is thrown.
   *
   * \param other: reference the matrix to be subtracted to produce the return matrix.
   * \return a new matrix: this - other.
   */

  Matrix<E> operator-(const Matrix<E> &other) const;

  /**
   * \brief Multiplies two matrices with appropriate dimensions.
   *
   * If the dimensions are not appropriate *ie*: this->getM()!=other.getN();
   * a runtime_error is thrown.
   *
   * \param other: reference the matrix to be multiplied to the right to produce the return matrix.
   * \return the product of the two matrices (*this * other).
   */
  Matrix<E> operator*(const Matrix<E> &other) const;

  /**
   * \brief Multiply each entry of the matrix by scalar s.
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * Does not modify the calling matrix.
   *
   * \return matrix M st M.get(i,j)==s*this->get(i,j) for all valid (i,j).
   */
  template <typename S> Matrix<E> operator*(const S &s) const;

  /**
   * \brief Adds matrix other to this matrix inplace.
   *
   * If the dimensions don't match, a runtime_error is thrown.
   *
   * \param other: reference to the matrix to be added to this matrix.
   * \return reference to this matrix after the addition is performed.
   */
  Matrix<E> &operator+=(const Matrix<E> &other);

  /**
   * \brief Subtracts matrix other from this matrix inplace.
   *
   * If the dimensions don't match, a runtime_error is thrown.
   *
   * \param other: reference to the matrix to be subtracted from this matrix.
   * \return reference to this matrix after the subtraction is performed.
   */
  Matrix<E> &operator-=(const Matrix<E> &other);

  /**
   * \brief Multiplies this matrix with other (inplace).
   *
   * If the dimensions are not appropriate *ie*: this->getM()!=other.getN();
   * a runtime_error is thrown.
   *
   * The dimensions of the matrix will change, the number of rows is guaranteed not to be altered.
   *
   * \param other: reference to the matrix to be multiplied to the right.
   * \return reference to this matrix after the multiplication is performed.
   */
  Matrix<E> &operator*=(const Matrix<E> &other);

  /**
   * \brief Multiply each entry of the matrix by scalar s (inplace).
   *
   * The type S is a "scalar" type; *ie*: a type that can be multiplied by an entry of type E
   * and yield a result of type E.
   *
   * \return reference to this matrix after all entries are multiplied by s.
   */
  template <typename S> Matrix<E> &operator*=(const S &s);

  /**
   * \brief Equality operator.
   * \param other: const reference to other matrix to be compared.
   * \return true iff the matrices have the same dimensions and
   * each corresponding entry compares equal. false otherwise.
   */
  bool operator==(const Matrix<E> &other) const;

  /**
   * \brief Inequality operator.
   * \param other: const reference to other matrix to be compared.
   * \return false iff the matrices have the same dimensions and
   * each corresponding entry compares equal. true otherwise.
   */
  bool operator!=(const Matrix<E> &other) const;

  /**
   * \brief Output matrix to ostream using <<. Compatible with reading in using >>.
   */
  template <typename T>
  friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix);

  /**
   * \brief Read matrix from istream using >>. Compatible with output using <<.
   */
  template <typename T>
  friend std::istream &operator>>(std::istream &is, Matrix<T> &matrix);

  /**
   * \brief Fill whole matrix with element E(e).
   * \return reference to the matrix after the operation is performed.
   */
  Matrix<E> &fill(E e);

  /**
   * \brief Fill matrix row with element E(e).
   *
   * Does bounds-checking.
   *
   * \return reference to the matrix after the operation is performed.
   */
  Matrix<E> &fillRow(int row, E e);

  /**
   * \brief Fill matrix column with element E(e).
   *
   * Does bounds-checking.
   *
   * \return reference to the matrix after the operation is performed.
   */
  Matrix<E> &fillColumn(int column, E e);
}; // class Matrix<E>

} // namespace linopt::inmemory

#include "Matrix.tpp"
#endif
