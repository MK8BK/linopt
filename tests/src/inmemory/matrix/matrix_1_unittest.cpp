#include "Matrix.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

using namespace linopt::inmemory;

TEST(Matrix, TestConstructor) {
    ASSERT_NO_THROW(Matrix<int> fr(1080, 1920););
    ASSERT_NO_THROW(Matrix<int> fb({{1, 2, 3},
                                    {4, 5, 6},
                                    {7, 8, 9}}););
    Matrix<int> fr(1080, 1920);
    ASSERT_NO_THROW(Matrix<int> fg(fr););
    ASSERT_NO_THROW(Matrix<int> fd(Matrix<int>(2, 45)););
    ASSERT_NO_THROW(Matrix<double> fd(1080, 1920, 12.34););
}

TEST(Matrix, TestAccess) {
    Matrix<long long> fr(1080, 1920);
    fr.fill(1342234LL).get(2, 3) = 5;
    ASSERT_EQ(fr.get(2, 3), 5);
    ASSERT_EQ(fr.get(2, 4), 1342234LL);
}

TEST(Matrix, TestAddition) {
    Matrix<long long> fr(1080, 1920);
    fr.fill(120LL);
    Matrix<long long> fg(1080, 1920);
    fg.fill(120LL);
    ASSERT_EQ(fr + fg, Matrix<long long>(1080, 1920).fill(240LL));
    ASSERT_EQ(Matrix<int>(255, 255, 4), Matrix<int>(255, 255, 2) + Matrix<int>(255, 255, 2));
}

TEST(Matrix, TestMatrixMultiplication) {
    Matrix<int> a{
            {1, 2, 3, 4},
            {4, 3, 2, 1},
            {1, 2, 3, 4}
    };
    Matrix<int> b{
            {5, 6},
            {6, 5},
            {5, 6},
            {6, 5}
    };
    ASSERT_EQ(a * b, Matrix<int>({{56, 54},
                                  {54, 56},
                                  {56, 54}}));
}

TEST(Matrix, TestScalarMultiplication) {
    Matrix<long long> m(1080, 1920, 100);
    ASSERT_EQ((m *= 2).get(500, 500), 200);
    ASSERT_EQ(Matrix<int>(2, 2, 2), Matrix<int>(2, 2, 1) * 2);
}

TEST(Matrix, TestRowMultiplication) {
    ASSERT_EQ(Matrix<int>({{1, 2},
                           {1, 2}}).multiplyRow(1, 3), Matrix<int>({{1, 2},
                                                                    {3, 6}}));
}

TEST(Matrix, TestColumnMultiplication) {
    ASSERT_EQ(Matrix<int>({{1, 2},
                           {1, 2}}).multiplyColumn(1, 3), Matrix<int>({{1, 6},
                                                                       {1, 6}}));
}

TEST(Matrix, TestRowCombination) {
    Matrix<int> m1({
                           {1, 0, 1},
                           {0, 1, 0},
                           {0, 0, 0}
                   });
    Matrix<int> m2({
                           {1, 0, 1},
                           {0, 1, 0},
                           {2, 1, 2}
                   });
    ASSERT_EQ(m1.combineRows(0, 2, 1, 1, 2), m2);
}

TEST(Matrix, TestColumnCombination) {
    Matrix<int> m1({
                           {1, 0, 1},
                           {0, 1, 0},
                           {0, 0, 0}
                   });
    Matrix<int> m2({
                           {1, 7, 1},
                           {0, 1, 0},
                           {0, 0, 0}
                   });
    ASSERT_EQ(m1.combineColumns(0, 7, 1, 1, 1), m2);
}

TEST(Matrix, TestInplaceTranspose) {
    Matrix<int> m1({
                           {1, 2, 1},
                           {0, 1, 0},
                           {0, 0, 5}
                   });
    Matrix<int> m2({
                           {1, 0, 0},
                           {2, 1, 0},
                           {1, 0, 5}
                   });
    ASSERT_EQ(m1.inplaceTranspose(), m2);
}

TEST(Matrix, TestTranspose) {
    Matrix<int> m1({
                           {1, 2, 1},
                           {0, 1, 0}
                   });
    Matrix<int> m2({
                           {1, 0},
                           {2, 1},
                           {1, 0}
                   });
    ASSERT_EQ(m1.transpose(), m2);
    ASSERT_THROW(m1.inplaceTranspose(), std::runtime_error);
}

TEST(Matrix, TestDimensions) {
    Matrix<int> m1(2, 3);
    Matrix<int> m2(3, 8);
    ASSERT_EQ(m1.getN(), 2);
    ASSERT_EQ(m1.getM(), 3);
    ASSERT_EQ((m1 + m1).getM(), 3);
    ASSERT_EQ((m1 + m1).getN(), 2);
    ASSERT_EQ((m1.transpose() * m1).getN(), 3);
    ASSERT_EQ((m1.transpose() * m1).getM(), 3);
    ASSERT_EQ((m1 * m1.transpose()).getN(), 2);
    ASSERT_EQ((m1 * m1.transpose()).getM(), 2);
    ASSERT_EQ((m1 * m2).getN(), 2);
    ASSERT_EQ((m1 * m2).getM(), 8);
}

TEST(Matrix, TestFill){
    Matrix<long long> m(200,300,3);
    m.fillColumn(2,8);
    m.fillRow(2,7);
    ASSERT_EQ(m.get(1,2),8);
    ASSERT_EQ(m.get(2,1),7);
    ASSERT_EQ(m.get(2,2), 7);
    ASSERT_EQ(m.get(3,3), 3);
}

TEST(Matrix, TestStreams) {
    Matrix<int> src(2, 2, 4);
    Matrix<int> dest(0, 0);
    std::stringstream s;
    s << src;
    s >> dest;
    ASSERT_EQ(dest, src);
    src = Matrix<int> (1080,1920,0).fillRow(539,255);
    std::fstream f("1920x1080.bin",std::ios_base::binary|std::ios_base::out);
    f << src;
    f.close();
    std::fstream fi("1920x1080.bin",std::ios_base::binary|std::ios_base::in);
    fi >> dest;
    ASSERT_EQ(dest, src);
    remove("1920x1080.bin");
}




