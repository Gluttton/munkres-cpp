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

#if !defined(__MUNKRES_CPP_MATRIX_BASE_H__)
#define __MUNKRES_CPP_MATRIX_BASE_H__

#include <cstdlib>
#include <limits>
#include <cmath>
#include <stdexcept>



namespace munkres_cpp
{

template<typename T>
class matrix_base
{
    public:
        // Types.
        using value_type = T;

        // Constants.
        static constexpr value_type zero = value_type (0);
        static constexpr value_type max_val = std::numeric_limits<value_type>::max ();

        // Interface.
        virtual ~matrix_base () = default;
        virtual const value_type & operator () (const size_t, const size_t) const = 0;
        virtual value_type & operator () (const size_t, const size_t) = 0;
        virtual size_t columns () const = 0;
        virtual size_t rows () const = 0;

        // Default implementation.
        virtual void resize (const size_t rows, const size_t columns, const value_type = zero)
        {
            if (rows != this->rows () || columns != this->columns () ) {
                throw std::logic_error ("Called function with inappropriate default implementation.");
            }
        }

        // Implementation.
        template <typename X = value_type>
        constexpr typename std::enable_if<std::is_integral<X>::value, bool>::type
        is_equal (const size_t row, const size_t column, const X & value) const
        {
            return operator () (row, column) == value;
        }

        template <typename X = value_type>
        constexpr typename std::enable_if<!std::is_integral<X>::value, bool>::type
        is_equal (const size_t row, const size_t column, const X & value) const
        {
            return FP_ZERO == std::fpclassify (operator () (row, column) - value);
        }

        bool is_zero (const size_t row, const size_t column) const
        {
            return is_equal (row, column, zero);
        }
};

template<typename T>
constexpr T matrix_base<T>::zero;

template<typename T>
constexpr T matrix_base<T>::max_val;

}// namespace munkres_cpp

#endif /* !defined(__MUNKRES_CPP_MATRIX_BASE_H__) */
