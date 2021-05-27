#pragma once
#include <iostream>
#include <fstream>
#include <complex>// if you make use of complex number facilities in C++
#include <thread>
#include <exception>

namespace Concurrent
{
    template <class T> struct RGB { T r, g, b; };

    const unsigned size = 10000;
    const unsigned height = 10000;


    class Mandelbrot
    {
    public:
        void mandelbrot(bool multithreaded);

        static int value(int x, int y);
    };

    template <class T>
    class Matrix {
    public:
        Matrix(const size_t rows, const size_t cols) : _rows(rows), _cols(cols) {
            _matrix = new T * [rows];
            for (size_t i = 0; i < rows; ++i) {
                _matrix[i] = new T[cols];
            }
        }
        Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols) {
            _matrix = new T * [m._rows];
            for (size_t i = 0; i < m._rows; ++i) {
                _matrix[i] = new T[m._cols];
                for (size_t j = 0; j < m._cols; ++j) {
                    _matrix[i][j] = m._matrix[i][j];
                }
            }
        }
        ~Matrix() {
            for (size_t i = 0; i < _rows; ++i) {
                delete[] _matrix[i];
            }
            delete[] _matrix;
        }

        //set the values for each "pixel" in the matrix.
        void SetValuesOfMatrix(int i, int y_max)
        {
            for (size_t y = i; y < y_max; y++)
            {
                printf("Currently working on: %i \n", y);

                for (size_t x = 0; x < width(); x++)
                {
                    _matrix[x][y].r = _matrix[x][y].g = _matrix[x][y].b = Mandelbrot::value(x, y);

                }
            }
        }



        T* operator[] (const size_t nIndex)
        {
            return _matrix[nIndex];
        }
        size_t width() const { return _cols; }
        size_t height() const { return _rows; }
    protected:
        size_t _rows, _cols;
        T** _matrix;
    };

    // Portable PixMap image
    class PPMImage : public Matrix<RGB<unsigned char> >
    {
    public:
        PPMImage(const size_t height, const size_t width) : Matrix(height, width) { }


        void save(const std::string& filename)
        {
            std::ofstream out(filename, std::ios_base::binary);
            out << "P6" << std::endl << _cols << " " << _rows << std::endl << 255 << std::endl;
            for (size_t y = 0; y < _rows; y++)
                for (size_t x = 0; x < _cols; x++)
                    out << _matrix[y][x].r << _matrix[y][x].g << _matrix[y][x].b;
        }
    };

}

