#include <gtest/gtest.h>
#include "munkres-cpp/utils.h"
#include "matrix_test.h"



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case001_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= 1.0;  e(0, 1)= 0.0;  e(0, 2)= 3.0;  e(0, 3)= 2.0;
    e(1, 0)= 3.0;  e(1, 1)=-2.0;  e(1, 2)=-1.0;  e(1, 3)= 0.0;
    e(2, 0)=-1.0;  e(2, 1)= 3.0;  e(2, 2)= 2.0;  e(2, 3)= 0.0;
    e(3, 0)=-1.0;  e(3, 1)= 0.0;  e(3, 2)= 2.0;  e(3, 3)= 3.0;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)= 1.0;  t(0, 1)= 0.0;  t(0, 2)= infinity;
                                                 t(0, 3)= 2.0;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-1.0;  t(1, 3)= 0.0;
    t(2, 0)=-1.0;  t(2, 1)=infinity;
                                  t(2, 2)= 2.0;  t(2, 3)= 0.0;
    t(3, 0)=-1.0;  t(3, 1)= 0.0;  t(3, 2)= 2.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    ASSERT_EQ (e.rows (), t.rows ());
    ASSERT_EQ (e.columns (), t.columns ());
    for (size_t j = 0; j < t.columns (); ++j) {
        for (size_t i = 0; i < t.rows (); ++i) {
            if ( (i == 0 && j == 2)
              || (i == 1 && j == 0)
              || (i == 2 && j == 1)
              || (i == 3 && j == 3) ) {
                SCOPED_TRACE (i);
                SCOPED_TRACE (j);
                EXPECT_TRUE (std::isfinite (t (i, j) ) );
                EXPECT_TRUE (t (i, j) > value_type (2.0) );
            }
            else {
                EXPECT_EQ (e (i, j), t (i, j) );
            }
        }
    }
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case002_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= 3.0;  e(0, 1)= 0.0;  e(0, 2)= 3.0;  e(0, 3)= 2.0;
    e(1, 0)= 3.0;  e(1, 1)=-2.0;  e(1, 2)=-1.0;  e(1, 3)= 3.0;
    e(2, 0)=-1.0;  e(2, 1)= 3.0;  e(2, 2)= 2.0;  e(2, 3)= 3.0;
    e(3, 0)=-1.0;  e(3, 1)= 3.0;  e(3, 2)= 2.0;  e(3, 3)= 3.0;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)=infinity;
                   t(0, 1)= 0.0;  t(0, 2)= infinity;
                                                 t(0, 3)= 2.0;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-1.0;  t(1, 3)=infinity;
    t(2, 0)=-1.0;  t(2, 1)=infinity;
                                  t(2, 2)= 2.0;  t(2, 3)=infinity;
    t(3, 0)=-1.0;  t(3, 1)=infinity;
                                  t(3, 2)= 2.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    ASSERT_EQ (e.rows (), t.rows ());
    ASSERT_EQ (e.columns (), t.columns ());
    for (size_t j = 0; j < t.columns (); ++j) {
        for (size_t i = 0; i < t.rows (); ++i) {
            if ( (i == 0 && j == 0)
              || (i == 0 && j == 2)
              || (i == 1 && j == 0)
              || (i == 1 && j == 3)
              || (i == 2 && j == 1)
              || (i == 2 && j == 3)
              || (i == 3 && j == 1)
              || (i == 3 && j == 3) ) {
                SCOPED_TRACE (i);
                SCOPED_TRACE (j);
                EXPECT_TRUE (std::isfinite (t (i, j) ) );
                EXPECT_TRUE (t (i, j) > value_type (2.0) );
            }
            else {
                EXPECT_EQ (e (i, j), t (i, j) );
            }
        }
    }
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case003_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)=-5.0;  e(0, 1)=-4.0;  e(0, 2)=-1.0;  e(0, 3)=-2.0;
    e(1, 0)=-1.0;  e(1, 1)=-2.0;  e(1, 2)=-5.0;  e(1, 3)=-4.0;
    e(2, 0)=-5.0;  e(2, 1)=-1.0;  e(2, 2)=-2.0;  e(2, 3)=-4.0;
    e(3, 0)=-5.0;  e(3, 1)=-4.0;  e(3, 2)=-2.0;  e(3, 3)=-1.0;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)=-5.0;  t(0, 1)=-4.0;  t(0, 2)= infinity;
                                                 t(0, 3)=-2.0;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-5.0;  t(1, 3)=-4.0;
    t(2, 0)=-5.0;  t(2, 1)=infinity;
                                  t(2, 2)=-2.0;  t(2, 3)=-4.0;
    t(3, 0)=-5.0;  t(3, 1)=-4.0;  t(3, 2)=-2.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    ASSERT_EQ (e.rows (), t.rows ());
    ASSERT_EQ (e.columns (), t.columns ());
    for (size_t j = 0; j < t.columns (); ++j) {
        for (size_t i = 0; i < t.rows (); ++i) {
            if ( (i == 0 && j == 2)
              || (i == 1 && j == 0)
              || (i == 2 && j == 1)
              || (i == 3 && j == 3) ) {
                SCOPED_TRACE (i);
                SCOPED_TRACE (j);
                EXPECT_TRUE (std::isfinite (t (i, j) ) );
                EXPECT_TRUE (t (i, j) > value_type (-2.0) );
            }
            else {
                EXPECT_EQ (e (i, j), t (i, j) );
            }
        }
    }
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case004_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= 1.0;  e(0, 1)= 0.0;  e(0, 2)= 3.0;  e(0, 3)= 2.0;
    e(1, 0)= 3.0;  e(1, 1)=-2.0;  e(1, 2)=-1.0;  e(1, 3)= 0.0;
    e(2, 0)=-1.0;  e(2, 1)= 3.0;  e(2, 2)= 0.0;  e(2, 3)= 0.0;
    e(3, 0)=-1.0;  e(3, 1)= 0.0;  e(3, 2)= 0.0;  e(3, 3)= 3.0;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)= 1.0;  t(0, 1)= 0.0;  t(0, 2)= infinity;
                                                 t(0, 3)= 2.0;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-1.0;  t(1, 3)= 0.0;
    t(2, 0)=-1.0;  t(2, 1)=infinity;
                                  t(2, 2)= 0.0;  t(2, 3)= 0.0;
    t(3, 0)=-1.0;  t(3, 1)= 0.0;  t(3, 2)= 0.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    ASSERT_EQ (e.rows (), t.rows ());
    ASSERT_EQ (e.columns (), t.columns ());
    for (size_t j = 0; j < t.columns (); ++j) {
        for (size_t i = 0; i < t.rows (); ++i) {
            if ( (i == 0 && j == 2)
              || (i == 1 && j == 0)
              || (i == 2 && j == 1)
              || (i == 3 && j == 3) ) {
                SCOPED_TRACE (i);
                SCOPED_TRACE (j);
                EXPECT_TRUE (std::isfinite (t (i, j) ) );
                EXPECT_TRUE (t (i, j) > value_type (2.0) );
            }
            else {
                EXPECT_EQ (e (i, j), t (i, j) );
            }
        }
    }
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case005_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    constexpr value_type max      = std::numeric_limits<value_type>::max ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= max;  e(0, 1)= max;  e(0, 2)= max;  e(0, 3)= max;
    e(1, 0)= max;  e(1, 1)= max;  e(1, 2)= max;  e(1, 3)= max;
    e(2, 0)= max;  e(2, 1)= max;  e(2, 2)= max;  e(2, 3)= max;
    e(3, 0)= max;  e(3, 1)= max;  e(3, 2)= max;  e(3, 3)= max;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)=infinity;
                   t(0, 1)=infinity;
                                  t(0, 2)=infinity;
                                                 t(0, 3)=infinity;
    t(1, 0)=infinity;
                   t(1, 1)=infinity;
                                  t(1, 2)=infinity;
                                                 t(1, 3)=infinity;
    t(2, 0)=infinity;
                   t(2, 1)=infinity;
                                  t(2, 2)=infinity;
                                                 t(2, 3)=infinity;
    t(3, 0)=infinity;
                   t(3, 1)=infinity;
                                  t(3, 2)=infinity;
                                                 t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<typename TypeParam::matrix_type <value_type> >, e, t);
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case006_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    constexpr value_type max      = std::numeric_limits<value_type>::max ();
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= 1.0;  e(0, 1)= 0.0;  e(0, 2)= max;  e(0, 3)= max;
    e(1, 0)= max;  e(1, 1)=-2.0;  e(1, 2)=-1.0;  e(1, 3)= 0.0;
    e(2, 0)=-1.0;  e(2, 1)= max;  e(2, 2)= 0.0;  e(2, 3)= 0.0;
    e(3, 0)=-1.0;  e(3, 1)= 0.0;  e(3, 2)= 0.0;  e(3, 3)= max;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)= 1.0;  t(0, 1)= 0.0;  t(0, 2)= infinity;
                                                 t(0, 3)= max;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-1.0;  t(1, 3)= 0.0;
    t(2, 0)=-1.0;  t(2, 1)=infinity;
                                  t(2, 2)= 0.0;  t(2, 3)= 0.0;
    t(3, 0)=-1.0;  t(3, 1)= 0.0;  t(3, 2)= 0.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<typename TypeParam::matrix_type <value_type> >, e, t);
}



TYPED_TEST (MunkresFloatingTest, replace_infinities_4x4Case007_Success)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    constexpr value_type infinity = std::numeric_limits<value_type>::infinity ();
    constexpr value_type max      = std::numeric_limits<value_type>::max ();
    const     value_type premax   = std::nextafter (std::numeric_limits<value_type>::max (), 0);
    typename TypeParam::matrix_type <value_type> e (4, 4);
    e(0, 0)= 1.0;  e(0, 1)= 0.0;  e(0, 2)= max;  e(0, 3)= 0.0;
    e(1, 0)= max;  e(1, 1)=-2.0;  e(1, 2)=-1.0;  e(1, 3)=premax;
    e(2, 0)=-1.0;  e(2, 1)= max;  e(2, 2)= 0.0;  e(2, 3)= 0.0;
    e(3, 0)=-1.0;  e(3, 1)= 0.0;  e(3, 2)= 0.0;  e(3, 3)= max;

    typename TypeParam::matrix_type <value_type> t (4, 4);
    t(0, 0)= 1.0;  t(0, 1)= 0.0;  t(0, 2)= infinity;
                                                 t(0, 3)= 0.0;
    t(1, 0)=infinity;
                   t(1, 1)=-2.0;  t(1, 2)=-1.0;  t(1, 3)=premax;
    t(2, 0)=-1.0;  t(2, 1)=infinity;
                                  t(2, 2)= 0.0;  t(2, 3)= 0.0;
    t(3, 0)=-1.0;  t(3, 1)= 0.0;  t(3, 2)= 0.0;  t(3, 3)=infinity;

    // Act.
    munkres_cpp::replace_infinites (t);

    // Assert.
    EXPECT_PRED2 (MatrixCompare<typename TypeParam::matrix_type <value_type> >, e, t);
}



TYPED_TEST (MunkresTest, is_data_valid_Success)
{
    // Arrange.
    typename TypeParam::matrix_type <typename TypeParam::value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)= 2.0;

    // Act, Assert.
    EXPECT_TRUE (munkres_cpp::is_data_valid (m) );
}



TYPED_TEST (MunkresSignedTest, is_data_valid_negative_Failed)
{
    // Arrange.
    typename TypeParam::matrix_type <typename TypeParam::value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)=-2.0;

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (m) );
}



TYPED_TEST (MunkresFloatingTest, is_data_valid_infinity_Failed)
{
    // Arrange.
    typename TypeParam::matrix_type <typename TypeParam::value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)= std::numeric_limits<typename TypeParam::value_type>::infinity ();

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (m) );
}



TYPED_TEST (MunkresFloatingTest, is_data_valid_minus_infinity_Failed)
{
    // Arrange.
    typename TypeParam::matrix_type <typename TypeParam::value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)=-std::numeric_limits<typename TypeParam::value_type>::infinity ();

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (m) );
}



TYPED_TEST (MunkresFloatingTest, is_data_valid_NaN_Failed)
{
    // Arrange.
    typename TypeParam::matrix_type <typename TypeParam::value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)=-std::numeric_limits<typename TypeParam::value_type>::quiet_NaN ();

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (m) );
}



TYPED_TEST (MunkresFloatingTest, is_data_valid_denormalized_Failed)
{
    using value_type = typename TypeParam::value_type;

    // Arrange.
    typename TypeParam::matrix_type <value_type> m (2, 2);
    m(0, 0)= 1.0;  m(0, 1)= 0.0;
    m(1, 0)= 3.0;  m(1, 1)=-std::numeric_limits<value_type>::min () / value_type (2.0);

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (m) );
}
