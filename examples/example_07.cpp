/*
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



// The most complex example of usage the library.
// How to create own matrix type using matrix_base helper.

// Include header with the solver class.
#include <munkres-cpp/munkres.h>

// The library provides set of adapters for the most popular containers.
// But if you need you can create adapter for any type of container by deriving
// from base matrix class and implement the basic functions which allows navigate
// on container and access to its data.

// Include header with the helper class for matrix implementation.
#include <munkres-cpp/matrix_base.h>
// Include header with validation functions.
#include <munkres-cpp/utils.h>
#include <vector>
#include <cstdlib>
#include <iostream>


// Custom matrix class that implements interface required by the solver.
template <typename T>
class SimpleMatrix : public munkres_cpp::matrix_base<T>
{
    public:
        SimpleMatrix (const size_t rows, const size_t columns)
        {
            data.resize (rows);
            for (size_t i = 0; i < data.size (); ++i) {
                data [i].resize (columns, 0);
            }
        }

        const T & operator () (const size_t row, const size_t column) const override
        {
            return data [row][column];
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return data [row][column];
        }

        size_t columns () const override
        {
            return data [0].size ();
        }

        size_t rows () const override
        {
            return data.size ();
        }

        void resize (size_t rows, size_t columns, T value = 0) override
        {
            data.resize (rows);
            for (size_t i = 0; i < rows; ++i) {
                data [i].resize (columns, value);
            }
        }

    private:
        std::vector <std::vector <T> > data;
};


int main (int /*argc*/, char * /*argv*/[])
{
    // Set input data (cost matrix) into your matrix.
    SimpleMatrix<float> data (3, 2);
    // The library can manage with non-square matrices.
    // In such case the library resize the input matrix and fill
    // new cells by sensible data.
    //           Task I           Task II
    data (0, 0) = 1; data (0, 1) = 2;   // Worker I
    data (1, 0) = 0; data (1, 1) = 9;   // Worker II
    data (2, 0) = 9; data (2, 1) = 9;   // Worker III
    // You are totally responsible for correctness of the input data.
    // Input data must be positive and well defined (no NaN or infinity).

    // If this corresponds logic of your problem domain you can replace
    // positive infinities on maximum value.
    munkres_cpp::replace_infinites (data);

    // The library provide generic function for checking is input data
    // correct and ready for processing. If you not sure in correctness
    // of the input data you should use it.
    if (munkres_cpp::is_data_valid (data) ) {
        // Next you need create the problem solver and pass data to it.
        munkres_cpp::Munkres<float, SimpleMatrix> solver (data);

        // Now the matrix contains the solution.
        // Zero value represents selected values.
        // For input above data the result will be:
        // Task I  Task II
        //   1,       0     // Worker I
        //   0,       1     // Worker II
        //   1,       1     // Worker III
        // Which means that sum of the costs 0 and 2 is equal 2 and
        // is minimum cost among the matrix.

        for (size_t i = 0; i < data.rows (); ++i) {
            for (size_t j = 0; j < data.columns (); ++j) {
                std::cout << data (i, j) << " ";
            }
            std::cout << std::endl;
        }

        return EXIT_SUCCESS;
    }
    else {
        return EXIT_FAILURE;
    }
}

