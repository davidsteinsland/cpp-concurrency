#ifndef THREAD_H
#define THREAD_H

#include <cstring>

namespace concurrency
{
	class thread
	{
		protected:
			void* thread_id;
			bool is_active;
			void (*thread_handler) (thread*);
			void* args;
			
		public:
		
		thread(void (*handle) (thread *))
		{
			thread_handler = handle;
		}
		
		thread(void (*handle) (thread *), void* arg)
		{
			thread_handler = handle;
			args = arg;
		}
		
		~thread();
		
		void* get_args()
		{
			return args;
		}
		
		void run()
		{
			if (thread_handler != NULL)
			{
				thread_handler(this);
			}
			
			is_active = false;
		}
		
		static void* run_helper(void*a)
		{
			((thread*)a)->run();
			
			return 0;
		}
		
		int start();
		void join();
		
		bool active()
		{
			return is_active;
		}
	};
};

#endif