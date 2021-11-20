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



// More complex example.
#include <munkres-cpp/munkres.h>
// The library provides set of adapters for the most popular containers.
// But if you need you can create adapter for any type of container by deriving
// from base matrix class and implement the basic functions which allows to navigate
// on container and access to its data.
#include <munkres-cpp/matrix_base.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <cstdlib>

// In general there are several approaches how to implement adapters:
// - use inheritance (inherited from both your container and
//   munkres_cpp::matrix_base);
// - use composition (inherited from munkres_cpp::matrix_base and use your
//   container as member);
template<class T>
class matrix_boost_adapter : public munkres_cpp::matrix_base<T>
{
    public:
        matrix_boost_adapter (boost::numeric::ublas::matrix<T> * data = nullptr)
            : data        {data}
            , is_own_data {false}
        {
            if (!data) {
                data = new boost::numeric::ublas::matrix<T>;
                is_own_data = true;
            }
        }

        matrix_boost_adapter (size_t rows, size_t columns)
            : data        {new boost::numeric::ublas::matrix<T> (rows, columns, 0)}
            , is_own_data {true}
        {
        }

        ~matrix_boost_adapter () override
        {
            if (is_own_data) {
                delete data;
            }
        }

        const T & operator () (const size_t row, const size_t column) const override
        {
            return data->operator () (row, column);
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return data->operator () (row, column);
        }

        size_t columns () const override
        {
            return data->size2 ();
        }

        size_t rows () const override
        {
            return data->size1 ();
        }

        void resize (size_t, size_t, T/* value = T (0) */) override
        {
        }

    private:
        boost::numeric::ublas::matrix<T> * data;
        bool is_own_data;
};

int main (int /*argc*/, char * /*argv*/[])
{
    // Create (or use already existed) matrix of your type.
    boost::numeric::ublas::matrix<double> data (2, 2);
    // Set input data (cost matrix).
    data (0, 0) = 1.0; data (0, 1) = 3.0;
    data (1, 0) = 5.0; data (1, 1) = 9.0;
    // Don't forget! You are responsible for correctness of the input data.

    // Create data adapter and pass your container to it.
    matrix_boost_adapter<double> adapter (& data);

    // Create the solver and pass data to it.
    munkres_cpp::Munkres<double, matrix_boost_adapter> solver (adapter);

    // Now the matrix contains the solution.

    return EXIT_SUCCESS;
}

