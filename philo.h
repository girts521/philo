#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <err.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_philosopher t_philosopher;

typedef struct s_fork
{
	t_mtx 	fork;
	int 	id;
} 		t_fork;

typedef struct s_data
{
	int number_of_philosophers;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	t_philosopher *philos;
	bool end_simulation;
	long 	start_simulation;
	t_fork *forks;
	bool threads_ready;
	t_mtx	data_mutex;
}				t_data;

typedef struct s_philosopher
{
	pthread_t thread;
	int id;
	t_fork *right_fork;
	t_fork *left_fork;
	bool full;
	int meals_counter;
	t_data *data;
}				t_philosopher;

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}			t_mutex_code;

typedef enum e_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}			t_time_code;

int		clean_error(char *message);
int		ft_strlen(char *str);
void    ft_putstr_fd(char *s, int fd);
long		ft_atoi(char *str);
void 	init_philo(t_data *data);
void 	*safe_malloc(size_t size);
void 	mutex_handle(t_mtx *mutex, t_mutex_code code);
void 	start_dinner(t_data *data);
void 	thread_handle(pthread_t *thread, void *(*foo)(void *),
                        void *data, t_mutex_code code);
void 	set_bool(t_mtx *mutex, bool *dest, bool value);
bool 	get_bool(t_mtx *mutex, bool *value);
void 	set_long(t_mtx *mutex, long *dest, long value);
bool 	get_long(t_mtx *mutex, long *value);
bool 	is_simulation_done(t_data *data);
void 	wait_threads(t_data *data);
long 	gettime(t_time_code code);
void precise_usleep(long usec, t_data *data);
