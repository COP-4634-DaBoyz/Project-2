#include <iostream>
#include <thread>
#include <pthread.h>

void rangeIsEven(int& n);
void rangeIsOdd(int& n);
void ex(int x);
int range = 2;
int numOfThreads = 1;
int p = 22;


int main(int argc, char* argv[])
{
	

	
	range = std::atoi(argv[1]);
	numOfThreads = std::atoi(argv[2]);

	std::thread threads[3];
	threads[0] = std::thread(ex, 1);
	threads[0].join();
	std::cout << p << std::endl;
	//std::cout << range << " " << numOfThreads << std::endl;
	/*
	while (range != 1)
	{
		if (range % 2 == 0)
		{
			//threads[0] = std::thread(rangeIsEven, 3);
			rangeIsEven(range);
		}
		else
		{
			rangeIsOdd(range);

		}
		std::cout << range << std::endl;
	}
	*/
	
}


void rangeIsEven(int& n)
{
	n = n / 2;
}

void rangeIsOdd(int& n)
{
	n = (3 * n) + 1;
}


void ex(int x)
{
	p = x;
}