#include "philo.h"
#include <stdlib.h>

static void *routine(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
//	ft_putstr_fd("works?\n id: %d\n", 2, philo->id);
//	printf("Works...id: %ld\n", philo->id);
	return NULL ;
}

void assign_forks(t_philosopher *philo, t_fork *forks, int pos)
{
	int number_of_philosophers;

	number_of_philosophers = philo->data->number_of_philosophers;
	if (philo->id % 2 || philo->id == 0)
	{
		philo->right_fork = &forks[pos];
		philo->left_fork = &forks[(pos + 1) % number_of_philosophers];
	}
	else
	{
		philo->left_fork = &forks[pos];
		philo->right_fork = &forks[(pos + 1) % number_of_philosophers];
	}

}

static void create_philo(t_data *data)
{
	int i;

	i = 0;
	while (i <= data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].meals_counter = 0;
		data->philos[i].data = data;

		assign_forks(&data->philos[i], data->forks, i);
	}
}

void init_philo(t_data *data)
{
	int i;

	data->end_simulation =  false;
	data->threads_ready = false;
	data->philos = safe_malloc((data->number_of_philosophers + 1) * sizeof(t_philosopher));
	data->forks = safe_malloc((data->number_of_philosophers + 1) * sizeof(t_fork));
	mutex_handle(&data->data_mutex, INIT);
	i = 1;
	while (i <= data->number_of_philosophers)
	{
		mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].id = i;
		i++;
	}
	create_philo(data);
}
