#ifndef CONDITION_VARIABLE_H
#define CONDITION_VARIABLE_H

#ifdef _WIN32
	#include <windows.h>
	
	typedef struct {HANDLE signal, broadcast;} cond_type;
#else
	#include <pthread.h>
	
	typedef pthread_cond_t cond_type;
#endif

#include "mutex.h"

namespace concurrency
{
	class condition_variable
	{
		private:
			cond_type cond_var;
		
		public:
			condition_variable();
			~condition_variable();
			
			void wait(mutex&);
			void notify_one();
			void notify_all();
	};
};

#endif