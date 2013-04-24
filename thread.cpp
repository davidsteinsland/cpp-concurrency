
#include "thread.h"

#ifdef _WIN32
	#include <windows.h>
	#include <process.h>
#else
	#include <pthread.h>
#endif

concurrency::thread::~thread()
{
}

int concurrency::thread::start()
{
	int retval = 0;

	#ifdef _WIN32
	retval = (long)_beginthreadex(NULL, 0, (unsigned int (__stdcall *)(void *))&thread::run_helper, this, 0, (unsigned int*)&thread_id) == 0 ? -1 : 0;
	#else
	retval = pthread_create ((pthread_t*)&thread_id, NULL, &thread::run_helper, this);
	#endif
	is_active = true;
	return retval;
}

void concurrency::thread::join()
{
	#ifdef _WIN32
	WaitForSingleObject( (HANDLE*)&thread_id, INFINITE);
	#else
	pthread_join ( *(pthread_t*)&thread_id, NULL );
	#endif
}