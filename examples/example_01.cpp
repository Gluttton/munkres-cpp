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



// Trivial example with obvious solution.

// Include header with the solver class.
#include <munkres-cpp/munkres.h>
// Include header with the built-in matrix class.
#include <munkres-cpp/matrix.h>
#include <cstdlib>

int main (int, char **)
{
    // Create an instance of matrix container and fill it with
    // input (cost) data.
    munkres_cpp::Matrix<unsigned> data {
    // Task I  Task II
        {1,       3}    // Worker I
       ,{5,       9}    // Worker II
    };

    // Next, create a problem solver and pass data to it.
    munkres_cpp::Munkres<unsigned, munkres_cpp::Matrix> solver (data);

    // Now the matrix contains the solution of the problem.
    // Zero value represents selected values.
    // For input above data the result will be:
    // Task I  Task II
    //   1,       0     // Worker I
    //   0,       1     // Worker II
    // That means that sum of the costs 3 and 5 is equal 8 and
    // is minimum cost among the matrix.

    return EXIT_SUCCESS;
}
