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

#if !defined(_MATRIX_H_)
#define _MATRIX_H_

#include "munkres-cpp/matrix_base.h"
#include "munkres-cpp/utils.h"
#include <initializer_list>
#include <cstdlib>
#include <algorithm>



namespace munkres_cpp
{

template<class T>
class Matrix : public matrix_base<T>
{
    public:
        Matrix ();
        Matrix (const size_t rows, const size_t columns);
        Matrix (const std::initializer_list<std::initializer_list<T>> & init);
        Matrix (const Matrix<T> & other);
        Matrix<T> & operator= (const Matrix<T> & other);
        ~Matrix () override;
        // All operations modify the matrix in-place.
        void resize (const size_t rows, const size_t columns, const T default_value = 0);
        void clear ();
        const T & operator () (const size_t x, const size_t y) const override;
        T & operator () (const size_t x, const size_t y) override;
        T min () const;
        T max () const;
        inline size_t minsize ()
        {
            return ( (m_rows < m_columns) ? m_rows : m_columns);
        }
        size_t columns () const override
        {
            return m_columns;
        }
        size_t rows () const override
        {
            return m_rows;
        }

    private:
        T ** m_matrix;
        size_t m_rows;
        size_t m_columns;
};



template<class T>
Matrix<T>::Matrix ()
    : m_matrix {nullptr}
    , m_rows {0}
    , m_columns {0}
{
    assert (!(m_matrix && m_rows && m_columns) );
}



template<class T>
Matrix<T>::Matrix (const std::initializer_list<std::initializer_list<T>> & init)
    : Matrix<T>()
{
    m_rows = init.size ();
    if (m_rows == 0) {
        m_columns = 0;
    } else {
        m_columns = init.begin ()->size ();
        if (m_columns > 0) {
            resize (m_rows, m_columns);
        }
    }

    size_t i = 0, j;
    for (auto row = init.begin (); row != init.end (); ++row, ++i) {
        assert (row->size () == m_columns);
        j = 0;
        for (auto value = row->begin (); value != row->end (); ++value, ++j) {
            m_matrix[i][j] = *value;
        }
    }
}



template<class T>
Matrix<T>::Matrix (const Matrix<T> & other)
{
    if (other.m_matrix != nullptr) {
        // Copy arrays.
        m_matrix = nullptr;
        resize (other.m_rows, other.m_columns);
        for (size_t i = 0; i < m_rows; i++) {
            for (size_t j = 0; j < m_columns; j++) {
                m_matrix[i][j] = other.m_matrix[i][j];
            }
        }
    } else {
        m_matrix = nullptr;
        m_rows = 0;
        m_columns = 0;
    }
}



template<class T>
Matrix<T>::Matrix (const size_t rows, const size_t columns)
    : m_matrix {nullptr}
{
    resize (rows, columns);
}



template<class T>
Matrix<T> & Matrix<T>::operator= (const Matrix<T> & other)
{
    if (other.m_matrix != nullptr) {
        // Copy arrays.
        resize (other.m_rows, other.m_columns);
        for (size_t i = 0; i < m_rows; i++) {
            for (size_t j = 0; j < m_columns; j++) {
                m_matrix[i][j] = other.m_matrix[i][j];
            }
        }
    } else {
        // Free arrays.
        for (size_t i = 0; i < m_columns; i++) {
            delete [] m_matrix[i];
        }

        delete [] m_matrix;

        m_matrix = nullptr;
        m_rows = 0;
        m_columns = 0;
    }

    return *this;
}



template<class T>
Matrix<T>::~Matrix ()
{
    if (m_matrix != nullptr) {
        // Free arrays.
        for (size_t i = 0; i < m_rows; i++) {
            delete [] m_matrix[i];
        }

        delete [] m_matrix;
    }
    m_matrix = nullptr;

    assert (m_matrix == nullptr);
}



template<class T>
void Matrix<T>::resize (const size_t rows, const size_t columns, const T default_value)
{
    assert (rows > 0);
    assert (columns > 0);

    if (m_matrix == nullptr) {
        // Alloc arrays.
        m_matrix = new T *[rows];           // Rows.
        for (size_t i = 0; i < rows; i++) {
            m_matrix[i] = new T[columns];   // Columns.
        }

        m_rows = rows;
        m_columns = columns;
        clear ();
    } else {
        // Save array pointer.
        T ** new_matrix;
        // Alloc new arrays.
        new_matrix = new T *[rows];         // Rows.
        for (size_t i = 0; i < rows; i++) {
            new_matrix[i] = new T[columns]; // Columns.
            for (size_t j = 0; j < columns; j++) {
                new_matrix[i][j] = default_value;
            }
        }

        // Copy data from saved pointer to new arrays.
        const size_t minrows = std::min (rows, m_rows);
        const size_t mincols = std::min (columns, m_columns);
        for (size_t x = 0; x < minrows; x++) {
            for (size_t y = 0; y < mincols; y++) {
                new_matrix[x][y] = m_matrix[x][y];
            }
        }

        // Delete old arrays.
        if (m_matrix != nullptr) {
            for (size_t i = 0; i < m_rows; i++) {
                delete [] m_matrix[i];
            }

            delete [] m_matrix;
        }

        m_rows = rows;
        m_columns = columns;
        m_matrix = new_matrix;
    }
}



template<class T>
void Matrix<T>::clear ()
{
    assert (m_matrix != nullptr);

    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_columns; j++) {
            m_matrix [i][j] = 0;
        }
    }
}



template<class T>
inline T & Matrix<T>::operator () (const size_t x, const size_t y)
{
    assert (x < m_rows);
    assert (y < m_columns);
    assert (m_matrix != nullptr);

    return m_matrix[x][y];
}



template<class T>
inline const T & Matrix<T>::operator () (const size_t x, const size_t y) const
{
    assert (x < m_rows);
    assert (y < m_columns);
    assert (m_matrix != nullptr);

    return m_matrix [x][y];
}



template<class T>
T Matrix<T>::min () const
{
    assert (m_matrix && m_rows && m_columns);

    T min = m_matrix [0][0];

    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_columns; j++) {
            min = std::min<T>(min, m_matrix [i][j]);
        }
    }

    return min;
}



template<class T>
T Matrix<T>::max () const
{
    assert (m_matrix && m_rows && m_columns);

    T max = m_matrix [0][0];

    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_columns; j++) {
            max = std::max<T>(max, m_matrix [i][j]);
        }
    }

    return max;
}

}// namespace munkres_cpp

#endif /* !defined(_MATRIX_H_) */

