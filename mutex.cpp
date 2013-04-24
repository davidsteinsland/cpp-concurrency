#include "mutex.h"

concurrency::mutex::mutex()
{
	#ifdef _WIN32
	mutex_var = CreateMutex(NULL, false, NULL);
	#else
	pthread_mutex_init (&mutex_var, NULL);
	#endif
}
concurrency::mutex::~mutex()
{
	#ifdef _WIN32
	CloseHandle(mutex_var);
	#else
	pthread_mutex_destroy(&mutex_var);
	#endif
}

void concurrency::mutex::lock()
{
	#ifdef _WIN32
	WaitForSingleObject(mutex_var, INFINITE);
	#else
	pthread_mutex_lock (&mutex_var);
	#endif
}

void concurrency::mutex::unlock()
{
	#ifdef _WIN32
	ReleaseMutex(mutex_var);
	#else
	pthread_mutex_unlock(&mutex_var);
	#endif
}

mutex_type& concurrency::mutex::get_mutex()
{
	return mutex_var;
}

concurrency::scoped_lock::scoped_lock (mutex& m) : mutex_var(m)
{
	mutex_var.lock();
}

concurrency::scoped_lock::~scoped_lock()
{
	mutex_var.unlock();
}