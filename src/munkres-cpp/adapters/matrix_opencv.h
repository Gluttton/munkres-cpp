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

#if !defined(_MUNKRES_ADAPTERS_OPENCV_MATRIX_H_)
#define _MUNKRES_ADAPTERS_OPENCV_MATRIX_H_

#include "munkres-cpp/matrix_base.h"
#include <opencv2/core/mat.hpp>

namespace munkres_cpp
{

template<class T>
class matrix_opencv : public matrix_base<T>, public cv::Mat_<T>
{
    public:
        using matrix_base<T>::begin;
        using matrix_base<T>::end;

        matrix_opencv (size_t rows, size_t columns)
            : cv::Mat_<T>::Mat_ (rows, columns, cv::DataType<T>::type)
        {
        }

        matrix_opencv (const matrix_opencv<T> & other)
                        : cv::Mat_<T>::Mat_ (other.clone () )
        {
        }

        matrix_opencv (const cv::Mat_<T> & other)
            : cv::Mat_<T>::Mat_ (other.clone () )
        {
        }

        matrix_opencv<T> & operator= (const matrix_opencv<T> & other)
        {
            other.copyTo (*this);
            return *this;
        }

        matrix_opencv<T> & operator= (const cv::Mat_<T> & other)
        {
            other.copyTo (*this);
            return *this;
        }

        const T & operator () (size_t row, size_t column) const override
        {
            return cv::Mat_<T>::operator () (row, column);
        };

        T & operator () (size_t row, size_t column) override
        {
            return cv::Mat_<T>::operator () (row, column);
        }

        size_t columns () const override
        {
            return cv::Mat_<T>::cols;
        }

        size_t rows () const override
        {
            return cv::Mat_<T>::rows;
        }
};

}// namespace munkres_cpp

#endif /* !defined(_MUNKRES_ADAPTERS_OPENCV_MATRIX_H_) */
