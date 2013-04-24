#include "mutex.h"
#include "condition_variable.h"
#include "thread.h"

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000);
#else
#include <unistd.h>
#endif

#include <iostream>
#include <queue>

std::queue<int> produced_nums;
concurrency::mutex m;
concurrency::condition_variable cond_var;

void _producer (concurrency::thread*t)
{
	std::cout << "Producer thread active" << std::endl;
	for (int i = 0; i < 5; ++i) {
		concurrency::scoped_lock lock(m);
		std::cout << "producing " << i << '\n';
		produced_nums.push(i);
		cond_var.notify_one();
	}   

	concurrency::scoped_lock lock(m);  
	cond_var.notify_one();
}

void _consumer (concurrency::thread*t)
{
	int consumer_id = (int) t->get_args();
	std::cout << "Consumer thread active" << std::endl;
	
	while (1)
	{
		{
			concurrency::scoped_lock lock(m);
			while (produced_nums.empty()) {  // loop to avoid spurious wakeups
				cond_var.wait(m);
			}   
			
			std::cout << "#" << consumer_id << " consuming " << produced_nums.front() << '\n';
			produced_nums.pop();
		}
		
		sleep(1);
	}  
}

int main()
{
	std::cout << "Test started ..." << std::endl;
	
    concurrency::thread producer(_producer); 
	
	if (producer.start() == -1)
		std::cerr << "Error whilst starting producer thread" << std::endl;
	
	sleep(1);
	
    concurrency::thread consumer(_consumer, (void*)1);
	
	if ( consumer.start() == -1)
		std::cerr << "Error whilst starting consumer thread" << std::endl;
	
	concurrency::thread consumer2(_consumer, (void*)2);
	
	if ( consumer2.start() == -1)
		std::cerr << "Error whilst starting consumer2 thread" << std::endl;
	
		
    producer.join();
    consumer.join();
    consumer2.join();
	
	while (producer.active() || consumer.active() || consumer2.active())
	{
		sleep(1);
	}
}