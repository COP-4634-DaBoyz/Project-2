#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <vector>

void rangeIsEven(int& n);
void rangeIsOdd(int& n);
void computeStoppingTime(int num);

std::mutex mtx;
int const HISTOGRAM_SIZE = 550;
int stopValue = 0;
int numOfThreads = 1;
int currentThread = 0;
int histogram[HISTOGRAM_SIZE];

int main(int argc, char* argv[])
{

	//init array with zeros 
	for (int i = 0; i < HISTOGRAM_SIZE; i++) 
		histogram[i] = 0;
	
	int range = 0;
	

	if (argv[1] != NULL)
	{
		range = std::atoi(argv[1]);
		numOfThreads = std::atoi(argv[2]);
	}

	std::thread threads[numOfThreads];

	if (argv[1] != NULL)
	{
		//start timer 
		for (int i = 2; i <= range; i++)
		{
			if (currentThread == numOfThreads) 
				currentThread = 0;

			threads[currentThread] = std::thread(computeStoppingTime, i);
			threads[currentThread].join();
			currentThread++;
		}	

		for (int i = 0; i < HISTOGRAM_SIZE; i++)
		{
			std::cout << i << ", " << histogram[i] << std::endl;
		}
		//end timer 
		//get histogram data and redirect output etc  
	}
}

void computeStoppingTime(int num)
{
	mtx.lock();
	stopValue = 0;
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
	histogram[stopValue] += 1;
	mtx.unlock();
}


void rangeIsEven(int& n)
{
	n = n / 2;
}

void rangeIsOdd(int& n)
{
	n = (3 * n) + 1;
}


