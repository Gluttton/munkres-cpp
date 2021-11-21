/*
 *   Copyright (c) 2021 Gluttton <gluttton@ukr.net>
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



// A complete real-life example of using the library.
// See README.md file for detailed description.

#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>

// Include header with the built-in matrix class.
#include <munkres-cpp/matrix.h>
// Include header with the solver class.
#include <munkres-cpp/munkres.h>



using point = std::pair <float, float>;



// Helper function to print matrix content.
template <typename T>
void PrintMatrix (const T & matrix)
{
    for (size_t i = 0; i < matrix.rows (); ++i) {
        for (size_t j = 0; j < matrix.columns (); ++j) {
            std::cout << matrix (i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



// Helper function to print vector of points.
void PrintPoints (const std::vector <point> & points)
{
    for (size_t i = 0; i < points.size (); ++i) {
        std::cout << points [i].first << ":" << points [i].second << std::endl;
    }
    std::cout << std::endl;
}



float Distance (const point & a, const point & b)
{
    const float dx = a.first  - b.first;
    const float dy = a.second - b.second;
    return std::hypot (dx, dy);
}



point Update (const point & estimation, const point & measurement)
{
    return {(estimation.first  + measurement.first)  / 2,
            (estimation.second + measurement.second) / 2};
}



int main (int, char **)
{
    std::vector <point> estimations {
        {1, 2} // A.
      , {6, 7} // B.
      , {2, 9} // C.
    };

    std::vector <point> measurements {
        {3, 4} // x.
      , {9, 6} // y.
      , {6, 8} // z.
    };

    std::cout << "Original estimations:" << std::endl;
    PrintPoints (estimations);

    std::cout << "Measurements:" << std::endl;
    PrintPoints (measurements);

    munkres_cpp::Matrix <float> data (estimations.size (), measurements.size () );
    for (size_t i = 0; i < estimations.size (); ++i) {
        for (size_t j = 0; j < measurements.size (); ++j) {
            data (i, j) = Distance (estimations [i], measurements [j]);
        }
    }
    std::cout << "Input cost data:" << std::endl;
    PrintMatrix (data);

    munkres_cpp::Munkres <float, munkres_cpp::Matrix> solver (data);
    std::cout << "Output solution data:" << std::endl;
    PrintMatrix (data);

    for (size_t i = 0; i < data.rows (); ++i) {
        for (size_t j = 0; j < data.columns (); ++j) {
            if (data (i, j) == 0) {
                estimations [i] = Update (estimations [i], measurements [j]);
            }
        }
    }

    std::cout << "Updated estimations:" << std::endl;
    PrintPoints (estimations);

    return EXIT_SUCCESS;
}
