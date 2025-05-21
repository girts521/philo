#include "philo.h"

static void mutex_error_handle(int status, t_mutex_code code)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (code == LOCK || code == UNLOCK))
		clean_error("Mutex value is invalid");
	else if (status == EINVAL && code == INIT)
		clean_error("Attr value is incorrect");
	else if (status == EDEADLK)
		clean_error("A Deadlock would occur if the thread blocked waiting for mutex");
	else if (status == EPERM)
		clean_error("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		clean_error("The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		clean_error("Mutex is locked")
}

void mutex_handle(t_mtx *mutex, t_mutex_code code)
{
	if (code == LOCK)
		mutex_error_handle(pthread_mutex_lock(mutex), code);	
	else if (code == UNLOCK)
		mutex_error_handle(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_error_handle(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		mutex_error_handle(pthread_mutex_destroy(mutex), code);
	else
	 	clean_error("Wrong mutex code passed for mutex handle!");
}

static void thread_error_handle(int status, t_mutex_code code)
{
	    if (status == 0)
        return ;
    if (status == EAGAIN)
        clean_error("No resources to create another thread");
    else if (status == EPERM)
        clean_error("The caller does not have appropriate permission\n");
    else if (status == EINVAL && code == CREATE)
        clean_error("The value specified by attr is invalid.");
    else if (status == EINVAL && ( code == JOIN || code == DETACH ))
        clean_error("The value specified by thread is not joinable\n");
    else if ( status == ESRCH)
        clean_error("No thread could be found corresponding to that "
                   "specified by the given thread ID, thread.");
    else if ( status == EDEADLK)
        clean_error("A deadlock was detected or the value of "
                   "thread specifies the calling thread.");
}

void thread_handle(pthread_t *thread, void *(*foo)(void *),
                        void *data, t_mutex_code code)
{
    if ( code == CREATE)
       thread_error_handle(pthread_create(thread, NULL, foo, data), code);
    else if (JOIN == code)
        thread_error_handle(pthread_join(*thread, NULL), code);
    else if (DETACH == code)
        thread_error_handle(pthread_detach(*thread), code);
    else
    	clean_error("Wrong opcode for thread handle:"
                   " use <CREATE> <JOIN> <DETACH>");
}
