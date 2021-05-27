// mandelbrot.cpp
// compile with: g++ -std=c++11 mandelbrot.cpp -o mandelbrot
// view output with: eog mandelbrot.ppm
#include "mandelbrot.h"
using namespace Concurrent;

void Mandelbrot::mandelbrot(bool multithreaded = false)
{
    PPMImage image(size, size);
    if (multithreaded)
    {
        try
        {
            //Makes 12 thread each calculating 1/6 of the mandelbrot values.
            int y = 0;
            int stepsize = size / 12;
            std::thread t1(&PPMImage::SetValuesOfMatrix, &image, y, stepsize);
            std::thread t2(&PPMImage::SetValuesOfMatrix, &image, y + stepsize, y + (stepsize * 2));
            std::thread t3(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 2), y + (stepsize * 3));
            std::thread t4(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 3), y + (stepsize * 4));
            std::thread t5(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 4), y + (stepsize * 5));
            std::thread t6(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 5), y + (stepsize * 6));
            std::thread t7(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 6), y + (stepsize * 7));
            std::thread t8(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 7), y + (stepsize * 8));
            std::thread t9(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 8), y + (stepsize * 9));
            std::thread t10(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 9), y + (stepsize * 10));
            std::thread t11(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 10), y + (stepsize * 11));
            std::thread t12(&PPMImage::SetValuesOfMatrix, &image, y + (stepsize * 11), y + (stepsize * 12));


            //Join the threads back together to generate the full mandelbrot.
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();
            t6.join();
            t7.join();
            t8.join();
            t9.join();
            t10.join();
            t11.join();
            t12.join();

        }
        //some exception handling used for debugging.
        catch (std::exception & e)
        {
            std::cout << e.what() << '\n';
        }
        catch (int e)
        {
            std::cout << e << "\n";
        }
    }
    else
    {
        for (size_t x = 0; x < size; x++)
        {
            image.SetValuesOfMatrix(x, size);
        }
    }
   

    image.save("mandelbrot.ppm");
}


//calculates the value for the individual pixels.
int Mandelbrot::value(int x, int y)
{
    std::complex<float> point((float)x / size - 1.5, (float)y / height - 0.5);
    std::complex<float> z(0, 0);
    unsigned int iterator = 0;

    while (abs(z) < 2 && iterator <= 25) {
        z = z * z + point;
        iterator++;
    }
    //Adds gradient instead of just black and white.
    if (iterator < 25) return (255 * iterator) / 24;
    else return 0;
}

int mandelbrot(double real, double imag) {
    int limit = 100;
    double zReal = real;
    double zImag = imag;

    for (int i = 0; i < limit; ++i) {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;

        if (r2 + i2 > 4.0) return i;

        zImag = 2.0 * zReal * zImag + imag;
        zReal = r2 - i2 + real;
    }
    return limit;
}
