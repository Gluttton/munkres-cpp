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


// How to integrate the library in the existing pipeline using adapter class.
// Example for OpenCV.

// Include header with the solver class.
#include <munkres-cpp/munkres.h>

// The library provides set of adapters for the most popular containers
// (for more info explore "adapters" folder).
// If you are lucky then adapter for your container is already implemented.

// Include header with the adapter for OpenCV matrix class.
#include <munkres-cpp/adapters/matrix_opencv.h>
#include <cstdlib>
#include <iostream>

// Let's suppose that a pipeline that modifies data stored in
// the OpenCV matrix container is already implemented.  And it is
// necessary to add one more processing step between existing ones.
//
//  Generate  >----->  Consume
//               ^
//               |
//             Solve


cv::Mat_<double> Generate ()
{
    cv::Mat_<double> data (2, 2);
    data (0, 0) = 1.0; data (0, 1) = 3.0;
    data (1, 0) = 5.0; data (1, 1) = 9.0;
    return data;
}


void Consume (cv::Mat_<double> & data)
{
    std::cout << data (0, 0) << " " << data (0, 1) << std::endl;
    std::cout << data (1, 0) << " " << data (1, 1) << std::endl;
}


int main (int /*argc*/, char * /*argv*/[])
{
    // Call the previous processing step that generates a variable
    // of type cv::Mat_ and pass the variable to adapter's constructor.
    munkres_cpp::matrix_opencv<double> data (Generate () );

    // Create the solver and pass the adapter instance to it.
    munkres_cpp::Munkres<double, munkres_cpp::matrix_opencv> solver (data);

    // Call the further processing step and pass the adapter variable to it.
    // Since the adapter class inherits the cv::Mat_ they are interchangeable.
    Consume (data);

    return EXIT_SUCCESS;
}
