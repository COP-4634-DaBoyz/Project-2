#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <vector>
#include <queue>

void rangeIsEven(int n);
void rangeIsOdd(int n);

int ZA_WARUDO = 0;
int numOfThreads = 1;
int currentThread = 0;
int counter = 0;
std::vector<int> histogram;


int main(int argc, char* argv[])
{
	
	int ceiling = 0;
	std::queue<int> holder;
	if (argv[1] != NULL )
	{
		ceiling = std::atoi(argv[1]);
		numOfThreads = std::atoi(argv[2]);
	}

	ZA_WARUDO = ceiling;
	std::mutex mtx;

	std::thread threads[numOfThreads];
	//threads[0] = std::thread(ex, range);
	//threads[0].join();
	//std::cout << range << std::endl;
	//std::cout << range << " " << numOfThreads << std::endl;
	if (argv[1] != NULL)
	{
		while (ZA_WARUDO != 1)
		{
			if (currentThread == numOfThreads)
				currentThread = 0;

			mtx.lock();
			if (ZA_WARUDO % 2 == 0)
			{
				threads[currentThread] = std::thread(rangeIsEven, ZA_WARUDO);
			}
			else
			{
				threads[currentThread] = std::thread(rangeIsOdd, ZA_WARUDO);
			}
			mtx.unlock();

			
			std::cout << ZA_WARUDO << std::endl;
			holder.push(ZA_WARUDO);
			threads[currentThread].join();
			currentThread++;
			counter++;
		}
		//resize to the highest value in the holder queue for the array to resize it later TODO 

		//std::cout << counter << "\n";
	}
}


void rangeIsEven(int n)
{
	ZA_WARUDO = n / 2;
}

void rangeIsOdd(int n)
{
	ZA_WARUDO = (3 * n) + 1;
}

