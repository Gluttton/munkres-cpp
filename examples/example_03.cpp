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



// Example with input data validation.

// Include header with the solver class.
#include <munkres-cpp/munkres.h>
// Include header with the built-in matrix class.
#include <munkres-cpp/matrix.h>
// Include header with validation functions.
#include <munkres-cpp/utils.h>
#include <cstdlib>

int main (int, char **)
{
    // Create an instance of matrix container and fill it with
    // input (cost) data.
    munkres_cpp::Matrix<int> data {
        {1,   3}
       ,{5,   9}
    };
    // You are totally responsible for correctness of the input data.
    // Input data must be positive and well defined (no NaN or infinity).

    // The library provide generic function for checking is input data
    // correct and ready for processing. If you not sure in correctness
    // of the input data you should use it.
    if (munkres_cpp::is_data_valid (data) ) {
        // Next you need to create the problem solver and pass data to it.
        munkres_cpp::Munkres<int, munkres_cpp::Matrix> solver (data);

        // Now the matrix contains the solution.
        // Zero value represents selected values.
        // For input above data the result will be:
        //   1,   0
        //   0,   1

        return EXIT_SUCCESS;
    }
    else {
        return EXIT_FAILURE;
    }
}

