/*
 *   Copyright (c) 2020 Gluttton
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

#if !defined(_ADAPTERS_TEST_H_)
#define _ADAPTERS_TEST_H_

#include "munkres-cpp/matrix.h"
#include "munkres-cpp/adapters/matrix_std_2d_vector.h"

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

#endif /* !defined(_ADAPTERS_TEST_H_) */
