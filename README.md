# linopt
Linear algebraic operations toolkit

## Guidelines to test

first install googletest as a git submodule
```bash
git submodule add git@github.com:google/googletest.git extern/googletest
git submodule 
git submodule update --init --recursive 
```

create a test file in /tests/
```cmake
# implementations of headers included by <TEST_FILE>
package_add_test(testname tests/<TEST_FILE>.cpp src/whatever.cpp)
```

run the tests
```bash
mkdir build
cd build
cmake .. && cmake --build .
make test
```


## Specifications
- read and write matrices from an input stream (file, network)
- store matrices in files
- perform matrix multiplications, transpositions, convolutions
- compute matrix eigenvalues and eigenvectors
- compute a matrix svd
- solve linear systems
  - iterative methods: Jacobi, Gauss-Seidel, Relaxation
  - gaussian elimination, LU, QR, Cholesky

## Resources and readings
- [`Modern CMake`](https://cliutils.gitlab.io/modern-cmake/)
- [`C++ <filesystem>`](https://en.cppreference.com/w/cpp/filesystem)
- [`Git Handbook`](https://www.freecodecamp.org/news/learn-git-basics/)
- [`Google Test Framework`](https://google.github.io/googletest/primer.html)
- [`Git - the simple guide`](https://rogerdudler.github.io/git-guide/)
- [`Mastering CMake book`](https://lrita.github.io/images/posts/cplusplus/mastering-cmake.pdf)

- [`BLAS`](https://www.boost.org/doc/libs/1_82_0/libs/numeric/ublas/doc/index.html)
- [`Numerical Linear Algebra`](http://mitran-lab.amath.unc.edu/courses/MATH662/biblio/AllaireKaber_2008_Book_NumericalLinearAlgebra.pdf)
- [`C++ refresher`](https://mk8bk.github.io/chapters/ccpp/cpp.html)
- [`CMake tutorial`](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

## Environment
- C++ standard 20
- cmake 3.22 minimum
- clang++-18 minimum
- git (whatever)
