#include "DiskMatrix.h"
#include <gtest/gtest.h>


TEST(DiskMatrix, Constructor){
  EXPECT_NO_THROW(DiskMatrix<double> d("m.lmf"));
}




