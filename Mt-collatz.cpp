#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <vector>
#include <sys/time.h>
#include <bits/stdc++.h> 

void rangeIsEven(int& n);
void rangeIsOdd(int& n);
void computeStoppingTime(int num);

std::mutex mtx;
int const HISTOGRAM_SIZE = 550;
int stopValue = 0;
int numOfThreads = 1;
int currentThread = 0;
int histogram[HISTOGRAM_SIZE];
int counter = 2;

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
	//std::cout << numOfThreads << "\n";
	std::thread threads[numOfThreads];

	if (argv[1] != NULL)
	{
		//start timer 
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);
		std::ios_base::sync_with_stdio(false);
		for (counter = 2; counter <= range; counter++)
		{
			if (currentThread == numOfThreads)
			{
				
				currentThread = 0;
				for (int i = 0; i < numOfThreads; i++)
					if(threads[i].joinable())
						threads[i].join();
			}
			
			threads[currentThread] = std::thread(computeStoppingTime, counter);
			//std::cout << "Thread: " << currentThread << " " << threads[currentThread].get_id() << "\n";


			currentThread++;
		}	
		

		for (int i = 0; i < numOfThreads; i++)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
				//std::cout << "joining1: " << i << "\n";
			}
				
		}

		clock_gettime(CLOCK_MONOTONIC, &end);

		double stopWatch;
		stopWatch = (end.tv_sec - start.tv_sec) * 1e9;
		stopWatch = (stopWatch + (end.tv_nsec - start.tv_nsec)) * 1e-9;
		
		for (int i = 0; i < HISTOGRAM_SIZE; i++)
		{
			std::cout << i << ", " << histogram[i] << std::endl;

			if(i == HISTOGRAM_SIZE-1) 
				std::cerr << range << ", " << numOfThreads << ", "<< std::fixed << stopWatch << std::setprecision(9) << std::endl;
		}
		
	}
}

void computeStoppingTime(int num)
{
	mtx.lock();
	stopValue = 0;
	while (num > 1)
	{
		if (num % 2 == 0)
			rangeIsEven(num);
		else	
			rangeIsOdd(num);

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


