#ifndef MUTEX_H
#define MUTEX_H

#ifdef _WIN32
	#include <windows.h>
	
	typedef HANDLE mutex_type;
#else
	#include <pthread.h>
	
	typedef pthread_mutex_t mutex_type;
#endif

namespace concurrency
{
	class mutex
	{
		private:
			mutex_type mutex_var;
		
		public:
			mutex();
			~mutex();
			
			void lock();
			void unlock();
			
			mutex_type& get_mutex();
	};
	
	class scoped_lock
	{
		private:
			mutex& mutex_var;
		
		public:
			scoped_lock(mutex&);
			~scoped_lock();
	};
};

#endif