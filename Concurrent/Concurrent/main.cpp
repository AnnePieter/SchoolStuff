#include <iostream>
#include "mandelbrot.h"
#include "dotproduct.h"
#include "tree.h"
//#include "threadpool.h"

#define Wait std::cout << "Press Enter to continue \n"; std::getLine() 

int exercise = 0;
using namespace Concurrent;
int main()
{
	Mandelbrot m = Mandelbrot();


	while (exercise != 7)
	{
		char arg = ' ';
		std::cout << "Welcome to my concurrency project please select the excercise you would like to execute by inputting the number associated with it: \n1. Mandelbrot single threaded \n2. Mandelbrot multithreaded.\n3. Dot product of two vectors with mutex\n4. Dot product of two vectors with atomic types.\n5. Evaluating an expression tree.\n6. Threadpool pattern\n7. Exit\nSelection: ";
		std::cin >> exercise;
		switch (exercise)
		{
		case 1:
			m.mandelbrot(false);
			exercise = 0;
			break;
		case 2:
			m.mandelbrot(true);
			exercise = 0;
			break;
		case 3:
			dotproduct(false);
			break;
		case 4:
			dotproduct(true);
			break;
		case 5:
			tree();
			break;
		case 6:
			// threadpool();
			break;
		case 7:
			return 0;
		default:
			std::cout << "Please input a number listed to continue";
		}
		while (arg != 'y' && arg != 'n') 
		{
			std::cout << "Do you want to continue [y/n]:";
			std::cin >> arg;
			switch (arg)
			{
			case 'y':
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
				break;
			case 'n':
				return 0;
			default:
				std::cout << "please use a lower case y or n\n";
			}
		}
	}



	return 0;
}