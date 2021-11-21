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

#if !defined(_MATRIX_TEST_UTILS_H_)
#define _MATRIX_TEST_UTILS_H_

#include "munkres-cpp/matrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <limits>

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



template<typename M>
bool MatrixCompare (const M & a, const M & b)
{
    if (a.rows () != b.rows () || a.columns () != b.columns () )
        return false;

    for (size_t row = 0; row < a.rows (); ++row)
        for (size_t col = 0; col < a.columns (); ++col)
            if (a (row, col) != b (row, col) )
                return false;

    return true;
}



template<class T>
std::ostream & print_matrix (std::ostream & os, const T & m)
{
    const std::string indent ("           ");
    os << "Matrix (" << &m << ") of " << m.rows () << "x" << m.columns () << std::endl;
    for (size_t row = 0; row < m.rows (); ++row) {
        os << indent;
        for (size_t col = 0; col < m.columns (); ++col) {
            os << std::setw (4) << std::setfill (' ') << m (row, col) << " ";
        }
        os << std::endl;
    }

    return os;
}

template<class T>
std::ostream & operator << (std::ostream & os, const munkres_cpp::Matrix<T> & m)
{
    return print_matrix (os, m);
}

#ifdef MUNKRES_CPP_BOOST
template<class T>
std::ostream & operator << (std::ostream & os, const munkres_cpp::matrix_boost<T> & m)
{
    return print_matrix (os, m);
}
#endif

#ifdef MUNKRES_CPP_EIGEN3
template<class T>
std::ostream & operator << (std::ostream & os, const munkres_cpp::matrix_eigen<T> & m)
{
    return print_matrix (os, m);
}
#endif

#ifdef MUNKRES_CPP_OPENCV
template<class T>
std::ostream & operator << (std::ostream & os, const munkres_cpp::matrix_opencv<T> & m)
{
    return print_matrix (os, m);
}
#endif

#ifdef MUNKRES_CPP_QT
template<class T, int N, int M>
std::ostream & operator << (std::ostream & os, const munkres_cpp::matrix_qt<T, N, M> & m)
{
    return print_matrix (os, m);
}
#endif

template<class T>
std::ostream & operator << (std::ostream & os, const munkres_cpp::matrix_std_2d_vector<T> & m)
{
    return print_matrix (os, m);
}



template<typename T>
std::istream & read_matrix (std::istream & is, T & m)
{
    std::string marker;
    is >> marker;
    if ("Matrix" == marker) {
        std::string unused;
        std::string size;
        is >> unused;
        is >> unused;
        is >> size;
        const size_t delimiter = size.find ("x");
        if (std::string::npos != delimiter) {
            const size_t rows = stoi (size.substr (0, delimiter) );
            const size_t columns = stoi (size.substr (delimiter + 1) );
            if (rows && columns) {
                T n (rows, columns);
                for (size_t row = 0; row < rows; ++row) {
                    for (size_t col = 0; col < columns; ++col) {
                        is >> n (row, col);
                    }
                }
                m = n;
            }
        }
    }

    return is;
}

template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::Matrix<T> & m)
{
    return read_matrix (is, m);
}

#if ARMADILLO_FOUND == 1
template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_armadillo<T> & m)
{
    return read_matrix (is, m);
}
#endif

#if BOOST_FOUND == 1
template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_boost<T> & m)
{
    return read_matrix (is, m);
}
#endif

#if EIGEN3_FOUND == 1
template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_eigen<T> & m)
{
    return read_matrix (is, m);
}
#endif

#if OPENCV_FOUND == 1
template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_opencv<T> & m)
{
    return read_matrix (is, m);
}
#endif

#if QT5_FOUND == 1
template<class T, int N, int M>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_qt<T, N, M> & m)
{
    return read_matrix (is, m);
}
#endif

template<class T>
std::istream & operator >> (std::istream & is, munkres_cpp::matrix_std_2d_vector<T> & m)
{
    return read_matrix (is, m);
}



const std::string fileName = "matrices.txt";



template<typename M>
bool write (const std::vector<M *> & matrices)
{
    std::fstream os;
    os.open (fileName, std::fstream::out);

    for (size_t i = 0; i < matrices.size (); ++i)
        os << *matrices [i];
    os.close ();

    return true;
}



template<typename M>
bool read (std::vector<M *> & matrices)
{
    std::fstream is;
    is.open (fileName, std::fstream::in);

    M * matrix = new M (1, 1);
    while (is >> * matrix) {
        matrices.push_back (matrix);
        matrix = new M (1, 1);
    }
    delete matrix;
    is.close ();

    return true;
}



template<
    typename T
  , typename V = typename T::matrix_base::value_type
  , typename D = std::uniform_real_distribution<typename std::conditional<std::is_integral<V>::value, double, V>::type> >
T generate_random_matrix (const int nrows, const int ncols)
{
    std::random_device device;
    std::mt19937 generator (device () );
    D distribution (0, std::numeric_limits<V>::max () );
    T matrix (nrows, ncols);
    std::for_each (
            matrix.munkres_cpp::matrix_base<V>::begin ()
          , matrix.munkres_cpp::matrix_base<V>::end ()
          , [&](V & v){v = distribution (generator);});

    return matrix;
}

#endif /* !defined(_MATRIX_TEST_UTILS_H_) */
