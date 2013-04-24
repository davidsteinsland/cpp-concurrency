#include "condition_variable.h"


concurrency::condition_variable::condition_variable()
{
	#ifdef _WIN32
	cond_var.signal = CreateEvent(NULL, false, false, NULL);
	cond_var.broadcast = CreateEvent(NULL, true, false, NULL);
	#else
	pthread_cond_init (&cond_var,NULL);
	#endif
}

concurrency::condition_variable::~condition_variable()
{
	#ifdef _WIN32
	#else
	pthread_cond_destroy(&cond_var);
	#endif
}

void concurrency::condition_variable::wait(mutex&m)
{
	#ifdef _WIN32
	m.unlock();
	
	HANDLE handles[] = {cond_var.signal, cond_var.broadcast};
	WaitForMultipleObjects(2, handles, false, INFINITE);
	
	m.lock();
	#else
		pthread_mutex_t mtx = m.get_mutex();
		pthread_cond_wait (&cond_var, &mtx);
	#endif
}

void concurrency::condition_variable::notify_one()
{
	#ifdef _WIN32
	SetEvent(cond_var.signal);
	#else
	pthread_cond_signal (&cond_var);
	#endif
}

void concurrency::condition_variable::notify_all()
{
	#ifdef _WIN32
	
	#else
	pthread_cond_broadcast (&cond_var);
	#endif
}