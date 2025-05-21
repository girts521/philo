#include "philo.h"

void *routine(void *data)
{
	t_philosopher *philo;

	philo = (t_philosopher *)data;
	wait_threads(philo->data); 
	
	return (NULL);
}

void start_dinner(t_data *data)
{
	int i;

	i = 0;

	while (i < data->number_of_philosophers)
	{
		thread_handle(&data->philos[i].thread, routine, &data->philos[i], CREATE);		
	}
	set_bool(&data->data_mutex, &data->threads_ready, true);
}
