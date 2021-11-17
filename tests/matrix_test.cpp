#include <gtest/gtest.h>
#include "matrix_test.h"
#include <iostream>
#include <iomanip>



template<typename TypeParam>
void resize_From1x1To2x2WithDefaultValueDefaulted_Success ()
{
    // Arrange.
    TypeParam e (2, 2);
    e(0, 0)=7.0;  e(0, 1)=0.0;
    e(1, 0)=0.0;  e(1, 1)=0.0;

    TypeParam t (1, 1);
    t(0, 0)=7.0;

    // Act.
    t.resize (2, 2);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<TypeParam>, e, t);
}

TYPED_TEST (MunkresTestMatrixMunkres, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixArmadillo, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixBoost, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixEigen, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixOpencv, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixStd2dvector, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
    resize_From1x1To2x2WithDefaultValueDefaulted_Success<TypeParam> ();
}



template<typename TypeParam>
void resize_From1x1To5x5WithDefaultValueDefaulted_Success ()
{
    // Arrange.
    TypeParam e (5, 5);
    e(0, 0)=7.0;  e(0, 1)=0.0;  e(0, 2)=0.0;  e(0, 3)=0.0;  e(0, 4)=0.0;
    e(1, 0)=0.0;  e(1, 1)=0.0;  e(1, 2)=0.0;  e(1, 3)=0.0;  e(1, 4)=0.0;
    e(2, 0)=0.0;  e(2, 1)=0.0;  e(2, 2)=0.0;  e(2, 3)=0.0;  e(2, 4)=0.0;
    e(3, 0)=0.0;  e(3, 1)=0.0;  e(3, 2)=0.0;  e(3, 3)=0.0;  e(3, 4)=0.0;
    e(4, 0)=0.0;  e(4, 1)=0.0;  e(4, 2)=0.0;  e(4, 3)=0.0;  e(4, 4)=0.0;

    TypeParam t (1, 1);
    t(0, 0)=7.0;

    // Act.
    t.resize (5, 5);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<TypeParam>, e, t);
}

TYPED_TEST (MunkresTestMatrixMunkres, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixArmadillo, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixBoost, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixEigen, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixOpencv, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixStd2dvector, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
    resize_From1x1To5x5WithDefaultValueDefaulted_Success<TypeParam> ();
}



template<typename TypeParam>
void resize_From5x5To3x3WithDefaultValueDefaulted_Success ()
{
    // Arrange.
    TypeParam e (3, 3);
    e(0, 0)=0.0;  e(0, 1)=0.1;  e(0, 2)=0.2;
    e(1, 0)=1.0;  e(1, 1)=1.1;  e(1, 2)=1.2;
    e(2, 0)=2.0;  e(2, 1)=2.1;  e(2, 2)=2.2;

    TypeParam t (5, 5);
    t(0, 0)=0.0;  t(0, 1)=0.1;  t(0, 2)=0.2;  t(0, 3)=0.3;  t(0, 4)=0.4;
    t(1, 0)=1.0;  t(1, 1)=1.1;  t(1, 2)=1.2;  t(1, 3)=1.3;  t(1, 4)=1.4;
    t(2, 0)=2.0;  t(2, 1)=2.1;  t(2, 2)=2.2;  t(2, 3)=2.3;  t(2, 4)=2.4;
    t(3, 0)=3.0;  t(3, 1)=3.1;  t(3, 2)=3.2;  t(3, 3)=3.3;  t(3, 4)=3.4;
    t(4, 0)=4.0;  t(4, 1)=4.1;  t(4, 2)=4.2;  t(4, 3)=4.3;  t(4, 4)=4.4;

    // Act.
    t.resize (3, 3);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<TypeParam>, e, t);
}

TYPED_TEST (MunkresTestMatrixMunkres, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixArmadillo, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixBoost, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixEigen, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixOpencv, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixStd2dvector, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
    resize_From5x5To3x3WithDefaultValueDefaulted_Success<TypeParam> ();
}



template<typename TypeParam>
void resize_From2x2To4x4WithDefaultValueExplicit_Success ()
{
    // Arrange.
    TypeParam e (4, 4);
    e(0, 0)=0.0;  e(0, 1)=0.1;  e(0, 2)=9.9;  e(0, 3)=9.9;
    e(1, 0)=1.0;  e(1, 1)=1.1;  e(1, 2)=9.9;  e(1, 3)=9.9;
    e(2, 0)=9.9;  e(2, 1)=9.9;  e(2, 2)=9.9;  e(2, 3)=9.9;
    e(3, 0)=9.9;  e(3, 1)=9.9;  e(3, 2)=9.9;  e(3, 3)=9.9;

    TypeParam t (2, 2);
    t(0, 0)=0.0;  t(0, 1)=0.1;
    t(1, 0)=1.0;  t(1, 1)=1.1;

    // Act.
    t.resize (4, 4, 9.9);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<TypeParam>, e, t);
}

TYPED_TEST (MunkresTestMatrixMunkres, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixArmadillo, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixBoost, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixEigen, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixOpencv, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}

TYPED_TEST (MunkresTestMatrixStd2dvector, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
    resize_From2x2To4x4WithDefaultValueExplicit_Success<TypeParam> ();
}



template<typename TypeParam>
void resize_bad_alloc_Throw ()
{
    // Arrange.
    TypeParam t (1, 1);
    t(0, 0)=0.0;

    // Act, Assert.
    EXPECT_THROW (t.resize (1, std::numeric_limits<size_t>::max () ), std::bad_alloc);
}

TYPED_TEST (MunkresTestMatrixMunkres, resize_bad_alloc_Throw)
{
    resize_bad_alloc_Throw<TypeParam> ();
}



class MatrixTest : public ::testing::Test
{
};



TEST_F (MatrixTest, operatorAssignment_0x0_Success)
{
    // Arrange.
    munkres_cpp::Matrix<double> etalon_matrix {std::initializer_list<std::initializer_list<double>>() };
    munkres_cpp::Matrix<double> test_matrix {
        {0.0, 0.1, 0.2},
        {3.0, 3.1, 3.2},
        {4.0, 4.1, 4.2}
    };

    // Act.
    test_matrix = etalon_matrix;

    // Assert.
    EXPECT_PRED2 (MatrixCompare<munkres_cpp::Matrix<double> >, etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, operatorAssignment_3x3_Success)
{
    // Arrange.
    munkres_cpp::Matrix<double> etalon_matrix {
        {0.0, 0.1, 0.2},
        {1.0, 1.1, 1.2},
        {2.0, 2.1, 2.2}
    };
    munkres_cpp::Matrix<double> test_matrix;

    // Act.
    test_matrix = etalon_matrix;

    // Assert.
    EXPECT_PRED2 (MatrixCompare<munkres_cpp::Matrix<double> >, etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, operatorSubscript_Success)
{
    // Arrange.
    munkres_cpp::Matrix<double> test_matrix {
        {0.0, 0.1, 0.2},
        {1.0, 1.1, 1.2},
        {2.0, 2.1, 2.2}
    };

    // Act, Assert.
    EXPECT_FLOAT_EQ ( 0.0, test_matrix (0, 0) );
    EXPECT_FLOAT_EQ ( 0.1, test_matrix (0, 1) );
    EXPECT_FLOAT_EQ ( 0.2, test_matrix (0, 2) );
    EXPECT_FLOAT_EQ ( 1.0, test_matrix (1, 0) );
    EXPECT_FLOAT_EQ ( 1.1, test_matrix (1, 1) );
    EXPECT_FLOAT_EQ ( 1.2, test_matrix (1, 2) );
    EXPECT_FLOAT_EQ ( 2.0, test_matrix (2, 0) );
    EXPECT_FLOAT_EQ ( 2.1, test_matrix (2, 1) );
    EXPECT_FLOAT_EQ ( 2.2, test_matrix (2, 2) );
}
