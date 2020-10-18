#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>

void rangeIsEven(int n);
void rangeIsOdd(int n);
//void ex(int x);
int range = 2;
int numOfThreads = 1;
int currentThread = 0;
//int p = 22;


int main(int argc, char* argv[])
{
	

	
	range = std::atoi(argv[1]);
	numOfThreads = std::atoi(argv[2]);
	std::mutex mtx;

	std::thread threads[numOfThreads];
	//threads[0] = std::thread(ex, range);
	//threads[0].join();
	//std::cout << range << std::endl;
	//std::cout << range << " " << numOfThreads << std::endl;
	
	while (range != 1)
	{
		if (currentThread == numOfThreads)
			currentThread = 0;

		mtx.lock();
		if (range % 2 == 0)
		{
			
			threads[currentThread] = std::thread(rangeIsEven, range);
		}
		else
		{
			threads[currentThread] = std::thread(rangeIsOdd, range);
		}
		mtx.unlock();

		std::cout << range << std::endl;
		threads[currentThread].join();
		currentThread++;
	}
	
	
}


void rangeIsEven(int n)
{
	range = n / 2;
}

void rangeIsOdd(int n)
{
	range = (3 * n) + 1;
}

/*
void ex(int x)
{
	range = x / 2;
}
*/