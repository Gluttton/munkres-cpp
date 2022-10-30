/*
 *   Copyright (c) 2007 John Weaver
 *   Copyright (c) 2016 Gluttton <gluttton@ukr.net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#if !defined(_MATRIX_TEST_H_)
#define _MATRIX_TEST_H_

#include "munkres-cpp/matrix.h"
#include "matrix_test_utils.h"

#if ARMADILLO_FOUND == 1
#include "munkres-cpp/adapters/matrix_armadillo.h"
#endif

#if BOOST_FOUND == 1
#include "munkres-cpp/adapters/matrix_boost.h"
#endif

#if EIGEN3_FOUND == 1
#include "munkres-cpp/adapters/matrix_eigen.h"
#endif

#if OPENCV_FOUND == 1
#include "munkres-cpp/adapters/matrix_opencv.h"
#endif

#if QT5_FOUND == 1
#include "munkres-cpp/adapters/matrix_qt.h"
#endif

#include "munkres-cpp/adapters/matrix_std_2d_vector.h"



template<typename V, template <typename> class M>
struct TypeHolder
{
    using value_type = V;

    template <typename X>
    using matrix_type = M <X>;
};

#if QT5_FOUND == 1
template <typename T>
using matrix_qt33 = munkres_cpp::matrix_qt <T, 3, 3>;
#endif

template <typename T> class MunkresTest : public ::testing::Test {};
typedef ::testing::Types <
      TypeHolder <int8_t,      munkres_cpp::Matrix>
    , TypeHolder <uint8_t,     munkres_cpp::Matrix>
    , TypeHolder <int16_t,     munkres_cpp::Matrix>
    , TypeHolder <uint16_t,    munkres_cpp::Matrix>
    , TypeHolder <int32_t,     munkres_cpp::Matrix>
    , TypeHolder <uint32_t,    munkres_cpp::Matrix>
    , TypeHolder <int64_t,     munkres_cpp::Matrix>
    , TypeHolder <uint64_t,    munkres_cpp::Matrix>
    , TypeHolder <float,       munkres_cpp::Matrix>
    , TypeHolder <double,      munkres_cpp::Matrix>
    , TypeHolder <long double, munkres_cpp::Matrix>
    #if ARMADILLO_FOUND == 1
    , TypeHolder <uint8_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <int16_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <uint16_t,    munkres_cpp::matrix_armadillo>
    , TypeHolder <int32_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <uint32_t,    munkres_cpp::matrix_armadillo>
    , TypeHolder <int64_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <uint64_t,    munkres_cpp::matrix_armadillo>
    , TypeHolder <float,       munkres_cpp::matrix_armadillo>
    , TypeHolder <double,      munkres_cpp::matrix_armadillo>
    #endif
    #if BOOST_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_boost>
    , TypeHolder <uint8_t,     munkres_cpp::matrix_boost>
    , TypeHolder <int16_t,     munkres_cpp::matrix_boost>
    , TypeHolder <uint16_t,    munkres_cpp::matrix_boost>
    , TypeHolder <int32_t,     munkres_cpp::matrix_boost>
    , TypeHolder <uint32_t,    munkres_cpp::matrix_boost>
    , TypeHolder <int64_t,     munkres_cpp::matrix_boost>
    , TypeHolder <uint64_t,    munkres_cpp::matrix_boost>
    , TypeHolder <float,       munkres_cpp::matrix_boost>
    , TypeHolder <double,      munkres_cpp::matrix_boost>
    , TypeHolder <long double, munkres_cpp::matrix_boost>
    #endif
    #if EIGEN3_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_eigen>
    , TypeHolder <uint8_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <int16_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <uint16_t,    munkres_cpp::matrix_eigen>
    , TypeHolder <int32_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <uint32_t,    munkres_cpp::matrix_eigen>
    , TypeHolder <int64_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <uint64_t,    munkres_cpp::matrix_eigen>
    , TypeHolder <float,       munkres_cpp::matrix_eigen>
    , TypeHolder <double,      munkres_cpp::matrix_eigen>
    , TypeHolder <long double, munkres_cpp::matrix_eigen>
    #endif
    #if OPENCV_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_opencv>
    , TypeHolder <uint8_t,     munkres_cpp::matrix_opencv>
    , TypeHolder <int16_t,     munkres_cpp::matrix_opencv>
    , TypeHolder <uint16_t,    munkres_cpp::matrix_opencv>
    , TypeHolder <int32_t,     munkres_cpp::matrix_opencv>
    , TypeHolder <float,       munkres_cpp::matrix_opencv>
    , TypeHolder <double,      munkres_cpp::matrix_opencv>
    #endif
    #if QT5_FOUND == 1
    #if 0
    , TypeHolder <int8_t,      matrix_qt33>
    , TypeHolder <uint8_t,     matrix_qt33>
    , TypeHolder <int16_t,     matrix_qt33>
    , TypeHolder <uint16_t,    matrix_qt33>
    , TypeHolder <int32_t,     matrix_qt33>
    , TypeHolder <uint32_t,    matrix_qt33>
    , TypeHolder <int64_t,     matrix_qt33>
    , TypeHolder <uint64_t,    matrix_qt33>
    , TypeHolder <float,       matrix_qt33>
    , TypeHolder <double,      matrix_qt33>
    , TypeHolder <long double, matrix_qt33>
    #endif
    #endif
    , TypeHolder <int8_t,      munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <uint8_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int16_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <uint16_t,    munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int32_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <uint32_t,    munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int64_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <uint64_t,    munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <float,       munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <double,      munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <long double, munkres_cpp::matrix_std_2d_vector>
    > MunkresTestTypes;
TYPED_TEST_SUITE (MunkresTest, MunkresTestTypes);



template <typename T> class MunkresSignedTest : public ::testing::Test {};
typedef ::testing::Types <
      TypeHolder <int8_t,      munkres_cpp::Matrix>
    , TypeHolder <int16_t,     munkres_cpp::Matrix>
    , TypeHolder <int32_t,     munkres_cpp::Matrix>
    , TypeHolder <int64_t,     munkres_cpp::Matrix>
    , TypeHolder <float,       munkres_cpp::Matrix>
    , TypeHolder <double,      munkres_cpp::Matrix>
    , TypeHolder <long double, munkres_cpp::Matrix>
    #if ARMADILLO_FOUND == 1
    , TypeHolder <int16_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <int32_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <int64_t,     munkres_cpp::matrix_armadillo>
    , TypeHolder <float,       munkres_cpp::matrix_armadillo>
    , TypeHolder <double,      munkres_cpp::matrix_armadillo>
    #endif
    #if BOOST_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_boost>
    , TypeHolder <int16_t,     munkres_cpp::matrix_boost>
    , TypeHolder <int32_t,     munkres_cpp::matrix_boost>
    , TypeHolder <int64_t,     munkres_cpp::matrix_boost>
    , TypeHolder <float,       munkres_cpp::matrix_boost>
    , TypeHolder <double,      munkres_cpp::matrix_boost>
    , TypeHolder <long double, munkres_cpp::matrix_boost>
    #endif
    #if EIGEN3_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_eigen>
    , TypeHolder <int16_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <int32_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <int64_t,     munkres_cpp::matrix_eigen>
    , TypeHolder <float,       munkres_cpp::matrix_eigen>
    , TypeHolder <double,      munkres_cpp::matrix_eigen>
    , TypeHolder <long double, munkres_cpp::matrix_eigen>
    #endif
    #if OPENCV_FOUND == 1
    , TypeHolder <int8_t,      munkres_cpp::matrix_opencv>
    , TypeHolder <int16_t,     munkres_cpp::matrix_opencv>
    , TypeHolder <int32_t,     munkres_cpp::matrix_opencv>
    , TypeHolder <float,       munkres_cpp::matrix_opencv>
    , TypeHolder <double,      munkres_cpp::matrix_opencv>
    #endif
    #if QT5_FOUND == 1
    #if 0
    , TypeHolder <int8_t,      matrix_qt33>
    , TypeHolder <int16_t,     matrix_qt33>
    , TypeHolder <int32_t,     matrix_qt33>
    , TypeHolder <int64_t,     matrix_qt33>
    , TypeHolder <float,       matrix_qt33>
    , TypeHolder <double,      matrix_qt33>
    , TypeHolder <long double, matrix_qt33>
    #endif
    #endif
    , TypeHolder <int8_t,      munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int16_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int32_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <int64_t,     munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <float,       munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <double,      munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <long double, munkres_cpp::matrix_std_2d_vector>
    > MunkresSignedTestTypes;
TYPED_TEST_SUITE (MunkresSignedTest, MunkresSignedTestTypes);



template <typename T> class MunkresFloatingTest : public ::testing::Test {};
typedef ::testing::Types <
      TypeHolder <float,       munkres_cpp::Matrix>
    , TypeHolder <double,      munkres_cpp::Matrix>
    , TypeHolder <long double, munkres_cpp::Matrix>
    #if ARMADILLO_FOUND == 1
    , TypeHolder <float,       munkres_cpp::matrix_armadillo>
    , TypeHolder <double,      munkres_cpp::matrix_armadillo>
    #endif
    #if BOOST_FOUND == 1
    , TypeHolder <float,       munkres_cpp::matrix_boost>
    , TypeHolder <double,      munkres_cpp::matrix_boost>
    , TypeHolder <long double, munkres_cpp::matrix_boost>
    #endif
    #if EIGEN3_FOUND == 1
    , TypeHolder <float,       munkres_cpp::matrix_eigen>
    , TypeHolder <double,      munkres_cpp::matrix_eigen>
    , TypeHolder <long double, munkres_cpp::matrix_eigen>
    #endif
    #if OPENCV_FOUND == 1
    , TypeHolder <float,       munkres_cpp::matrix_opencv>
    , TypeHolder <double,      munkres_cpp::matrix_opencv>
    #endif
    #if QT5_FOUND == 1
    #if 0
    , TypeHolder <float,       matrix_qt33>
    , TypeHolder <double,      matrix_qt33>
    , TypeHolder <long double, matrix_qt33>
    #endif
    #endif
    , TypeHolder <float,       munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <double,      munkres_cpp::matrix_std_2d_vector>
    , TypeHolder <long double, munkres_cpp::matrix_std_2d_vector>
    > MunkresFloatingTestTypes;
TYPED_TEST_SUITE (MunkresFloatingTest, MunkresFloatingTestTypes);

#endif /* !defined(_MATRIX_TEST_H_) */
