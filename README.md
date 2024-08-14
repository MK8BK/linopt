# linopt
Linear algebraic operations toolkit

## Developement Guidelines and Resources

Install the boost library, and make sure your installation's
`bin` directory is included in your path variable.

```bash
$ mkdir build # if no build directory is present
$ cd build
$ cmake .. -G YOUR_GENERATOR # Ninja or Unix Makefiles are the most common
$ cmake --build . # build the project
$ ctest # run all the tests
$ # make sure doxygen is installed 
$ cd docs # if not already in docs directory
$ doxygen # build the documentation, visit the /docs/html/index.html file
```

Helpful documents for development:

We use the [`Google Test Framework`](http://google.github.io/googletest/)
for testing.

We use CMake to build the source code, a helpful (NON-FREE) book to understand
cmake is 
[`Professional CMake`](https://crascit.com/professional-cmake/).

We use the
[`Boost.Log `](https://www.boost.org/doc/libs/1_85_0/libs/log/doc/html/index.html)
logging library.

We use the Javadoc style comments with doxygen.
See the details of this style on the 
[`documenting the code`](https://www.doxygen.nl/manual/docblocks.html)
page of doxygen. (CTRL+f "Using the Javadoc style").

Some git articles:
- [`Git - the simple guide`](https://rogerdudler.github.io/git-guide/)
- [`Git Handbook`](https://www.freecodecamp.org/news/learn-git-basics/)

C++ language refereshers:
- [`C++ <filesystem>`](https://en.cppreference.com/w/cpp/filesystem)
- [`C++ refresher`](https://mk8bk.github.io/chapters/ccpp/cpp.html)

## Specification
- read and write matrices from an input stream (file, network)
- store matrices in files
- perform matrix multiplications, transpositions, convolutions
- compute matrix eigenvalues and eigenvectors
- compute a matrix svd
- solve linear systems
  - iterative methods: Jacobi, Gauss-Seidel, Relaxation
  - gaussian elimination, LU, QR, Cholesky

## Resources and readings
- [`Numerical Linear Algebra`](http://mitran-lab.amath.unc.edu/courses/MATH662/biblio/AllaireKaber_2008_Book_NumericalLinearAlgebra.pdf)
- [`BLAS`](https://www.boost.org/doc/libs/1_82_0/libs/numeric/ublas/doc/index.html)
- [`RandNLA Survey`](https://arxiv.org/pdf/2302.11474)

## Approximate Environment
- C++ standard 20
- cmake 3.22 minimum
- clang++-18 minimum
- boost - 1.85.0 minimum (did not check earlier versions)
- git (whatever)
- doxygen
