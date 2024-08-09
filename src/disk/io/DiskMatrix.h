/**
 * @file DiskMatrix.h
 * @author mk8bk
 * @brief 
 * @version 0.1
 * @date 09/08/2024
 * @copyright Copyright (c) 2024
 */



#ifndef DISKMATRIX_H
#define DISKMATRIX_H
#include <filesystem>

/**
* The DiskMatrix class represents a matrix stored on the filesystem.
* DiskMatrix objects may be opened or closed. They provide an interface
* to perform the following common matrix operations:
*   - addition
*   - multiplication
*   - hadamard product
*   - pointwise function application
*   - transpose
*   - inverse
*   - element access
* This class is an abstract class, it does not enforce any format used
* to encode the matrix on the filesystem.
*/
template<typename T>
class DiskMatrix final { 
private:
  /**
  * The path at which the matrix is stored. The file name usually a .lmf.
  * This file format is detailed @lmf.
  */
  std::filesystem::path p;
public:
  ~DiskMatrix();
  DiskMatrix();
};

#endif
