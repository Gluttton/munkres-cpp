/*
 *   Copyright (c) 2007 John Weaver
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

#ifdef MUNKRES_CPP_ARMADILLO
#include "munkres-cpp/adapters/matrix_armadillo.h"
#endif

#ifdef MUNKRES_CPP_BOOST
#include "munkres-cpp/adapters/matrix_boost.h"
#endif

#ifdef MUNKRES_CPP_EIGEN3
#include "munkres-cpp/adapters/matrix_eigen.h"
#endif

#ifdef MUNKRES_CPP_OPENCV
#include "munkres-cpp/adapters/matrix_opencv.h"
#endif

#ifdef MUNKRES_CPP_QT
#include "munkres-cpp/adapters/matrix_qt.h"
#endif

#include "munkres-cpp/adapters/matrix_std_2d_vector.h"



template <typename T> class MunkresTest : public ::testing::Test {};
typedef ::testing::Types <
      munkres_cpp::Matrix               <int8_t>
    , munkres_cpp::Matrix               <uint8_t>
    , munkres_cpp::Matrix               <int16_t>
    , munkres_cpp::Matrix               <uint16_t>
    , munkres_cpp::Matrix               <int32_t>
    , munkres_cpp::Matrix               <uint32_t>
    , munkres_cpp::Matrix               <int64_t>
    , munkres_cpp::Matrix               <uint64_t>
    , munkres_cpp::Matrix               <float>
    , munkres_cpp::Matrix               <double>
    , munkres_cpp::Matrix               <long double>
    #ifdef MUNKRES_CPP_ARMADILLO
    , munkres_cpp::matrix_armadillo     <uint8_t>
    , munkres_cpp::matrix_armadillo     <int16_t>
    , munkres_cpp::matrix_armadillo     <uint16_t>
    , munkres_cpp::matrix_armadillo     <int32_t>
    , munkres_cpp::matrix_armadillo     <uint32_t>
    , munkres_cpp::matrix_armadillo     <int64_t>
    , munkres_cpp::matrix_armadillo     <uint64_t>
    , munkres_cpp::matrix_armadillo     <float>
    , munkres_cpp::matrix_armadillo     <double>
    #endif
    #ifdef MUNKRES_CPP_BOOST
    , munkres_cpp::matrix_boost         <int8_t>
    , munkres_cpp::matrix_boost         <uint8_t>
    , munkres_cpp::matrix_boost         <int16_t>
    , munkres_cpp::matrix_boost         <uint16_t>
    , munkres_cpp::matrix_boost         <int32_t>
    , munkres_cpp::matrix_boost         <uint32_t>
    , munkres_cpp::matrix_boost         <int64_t>
    , munkres_cpp::matrix_boost         <uint64_t>
    , munkres_cpp::matrix_boost         <float>
    , munkres_cpp::matrix_boost         <double>
    , munkres_cpp::matrix_boost         <long double>
    #endif
    #ifdef MUNKRES_CPP_EIGEN3
    , munkres_cpp::matrix_eigen         <int8_t>
    , munkres_cpp::matrix_eigen         <uint8_t>
    , munkres_cpp::matrix_eigen         <int16_t>
    , munkres_cpp::matrix_eigen         <uint16_t>
    , munkres_cpp::matrix_eigen         <int32_t>
    , munkres_cpp::matrix_eigen         <uint32_t>
    , munkres_cpp::matrix_eigen         <int64_t>
    , munkres_cpp::matrix_eigen         <uint64_t>
    , munkres_cpp::matrix_eigen         <float>
    , munkres_cpp::matrix_eigen         <double>
    , munkres_cpp::matrix_eigen         <long double>
    #endif
    #ifdef MUNKRES_CPP_OPENCV
    , munkres_cpp::matrix_opencv        <int8_t>
    , munkres_cpp::matrix_opencv        <uint8_t>
    , munkres_cpp::matrix_opencv        <int16_t>
    , munkres_cpp::matrix_opencv        <uint16_t>
    , munkres_cpp::matrix_opencv        <int32_t>
    , munkres_cpp::matrix_opencv        <float>
    , munkres_cpp::matrix_opencv        <double>
    #endif
    #ifdef MUNKRES_CPP_QT
    #if 0
    , munkres_cpp::matrix_qt            <int8_t,      3, 3>
    , munkres_cpp::matrix_qt            <uint8_t,     3, 3>
    , munkres_cpp::matrix_qt            <int16_t,     3, 3>
    , munkres_cpp::matrix_qt            <uint16_t,    3, 3>
    , munkres_cpp::matrix_qt            <int32_t,     3, 3>
    , munkres_cpp::matrix_qt            <uint32_t,    3, 3>
    , munkres_cpp::matrix_qt            <int64,       3, 3>
    , munkres_cpp::matrix_qt            <uint64,      3, 3>
    , munkres_cpp::matrix_qt            <float,       3, 3>
    , munkres_cpp::matrix_qt            <double,      3, 3>
    , munkres_cpp::matrix_qt            <long double, 3, 3>
    #endif
    #endif
    , munkres_cpp::matrix_std_2d_vector <int8_t>
    , munkres_cpp::matrix_std_2d_vector <uint8_t>
    , munkres_cpp::matrix_std_2d_vector <int16_t>
    , munkres_cpp::matrix_std_2d_vector <uint16_t>
    , munkres_cpp::matrix_std_2d_vector <int32_t>
    , munkres_cpp::matrix_std_2d_vector <uint32_t>
    , munkres_cpp::matrix_std_2d_vector <int64_t>
    , munkres_cpp::matrix_std_2d_vector <uint64_t>
    , munkres_cpp::matrix_std_2d_vector <float>
    , munkres_cpp::matrix_std_2d_vector <double>
    , munkres_cpp::matrix_std_2d_vector <long double>
    > MunkresTestTypes;
TYPED_TEST_SUITE (MunkresTest, MunkresTestTypes);



template <typename T> class MunkresSignedTest : public ::testing::Test {};
typedef ::testing::Types <
      munkres_cpp::Matrix               <int8_t>
    , munkres_cpp::Matrix               <int16_t>
    , munkres_cpp::Matrix               <int32_t>
    , munkres_cpp::Matrix               <int64_t>
    , munkres_cpp::Matrix               <float>
    , munkres_cpp::Matrix               <double>
    , munkres_cpp::Matrix               <long double>
    #ifdef MUNKRES_CPP_ARMADILLO
    , munkres_cpp::matrix_armadillo     <int16_t>
    , munkres_cpp::matrix_armadillo     <int32_t>
    , munkres_cpp::matrix_armadillo     <int64_t>
    , munkres_cpp::matrix_armadillo     <float>
    , munkres_cpp::matrix_armadillo     <double>
    #endif
    #ifdef MUNKRES_CPP_BOOST
    , munkres_cpp::matrix_boost         <int8_t>
    , munkres_cpp::matrix_boost         <int16_t>
    , munkres_cpp::matrix_boost         <int32_t>
    , munkres_cpp::matrix_boost         <int64_t>
    , munkres_cpp::matrix_boost         <float>
    , munkres_cpp::matrix_boost         <double>
    , munkres_cpp::matrix_boost         <long double>
    #endif
    #ifdef MUNKRES_CPP_EIGEN3
    , munkres_cpp::matrix_eigen         <int8_t>
    , munkres_cpp::matrix_eigen         <int16_t>
    , munkres_cpp::matrix_eigen         <int32_t>
    , munkres_cpp::matrix_eigen         <int64_t>
    , munkres_cpp::matrix_eigen         <float>
    , munkres_cpp::matrix_eigen         <double>
    , munkres_cpp::matrix_eigen         <long double>
    #endif
    #ifdef MUNKRES_CPP_OPENCV
    , munkres_cpp::matrix_opencv        <int8_t>
    , munkres_cpp::matrix_opencv        <int16_t>
    , munkres_cpp::matrix_opencv        <int32_t>
    , munkres_cpp::matrix_opencv        <float>
    , munkres_cpp::matrix_opencv        <double>
    #endif
    , munkres_cpp::matrix_std_2d_vector <int8_t>
    , munkres_cpp::matrix_std_2d_vector <int16_t>
    , munkres_cpp::matrix_std_2d_vector <int32_t>
    , munkres_cpp::matrix_std_2d_vector <int64_t>
    , munkres_cpp::matrix_std_2d_vector <float>
    , munkres_cpp::matrix_std_2d_vector <double>
    , munkres_cpp::matrix_std_2d_vector <long double>
    > MunkresSignedTestTypes;
TYPED_TEST_SUITE (MunkresSignedTest, MunkresSignedTestTypes);



template <typename T> class MunkresFloatingTest : public ::testing::Test {};
typedef ::testing::Types <
      munkres_cpp::Matrix               <float>
    , munkres_cpp::Matrix               <double>
    , munkres_cpp::Matrix               <long double>
    #ifdef MUNKRES_CPP_ARMADILLO
    , munkres_cpp::matrix_armadillo     <float>
    , munkres_cpp::matrix_armadillo     <double>
    #endif
    #ifdef MUNKRES_CPP_BOOST
    , munkres_cpp::matrix_boost         <float>
    , munkres_cpp::matrix_boost         <double>
    , munkres_cpp::matrix_boost         <long double>
    #endif
    #ifdef MUNKRES_CPP_EIGEN3
    , munkres_cpp::matrix_eigen         <float>
    , munkres_cpp::matrix_eigen         <double>
    , munkres_cpp::matrix_eigen         <long double>
    #endif
    #ifdef MUNKRES_CPP_OPENCV
    , munkres_cpp::matrix_opencv        <float>
    , munkres_cpp::matrix_opencv        <double>
    #endif
    , munkres_cpp::matrix_std_2d_vector <float>
    , munkres_cpp::matrix_std_2d_vector <double>
    , munkres_cpp::matrix_std_2d_vector <long double>
    > MunkresFloatingTestTypes;
TYPED_TEST_SUITE (MunkresFloatingTest, MunkresFloatingTestTypes);

#endif /* !defined(_MATRIX_TEST_H_) */
