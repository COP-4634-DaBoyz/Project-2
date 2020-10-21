#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <vector>
#include <queue>

void rangeIsEven(int& n);
void rangeIsOdd(int& n);
void computeStoppingTime(int num);

int stopValue = 0;
int numOfThreads = 1;
int currentThread = 0;
int counter = 0;
int histogram[550];

int main(int argc, char* argv[])
{
	
	int range = 0;
	std::mutex mtx;
	std::thread threads[numOfThreads];

	if (argv[1] != NULL )
	{
		range = std::atoi(argv[1]);
		numOfThreads = std::atoi(argv[2]);
	}

	if (argv[1] != NULL)
	{
		for (int i = 2; i <= range; i++)
		{
			if (currentThread == numOfThreads) 
				currentThread = 0;
			
			mtx.lock();
			stopValue = 0;
			threads[currentThread] = std::thread(computeStoppingTime, i);
			mtx.unlock();

			//std::cout << i << std::endl;
			threads[currentThread].join();
		}
	}
}

void computeStoppingTime(int num)
{

	while (num > 1)
	{
		if (num % 2 == 0)
		{
			rangeIsEven(num);
		}
		else
		{
			rangeIsOdd(num);
		}
		stopValue++;
	}

	if (stopValue > 550)
	{
		//std::cout << stopValue << std::endl;

	}
}


void rangeIsEven(int& n)
{
	n = n / 2;
}

void rangeIsOdd(int& n)
{
	n = (3 * n) + 1;
}

