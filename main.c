#include "philo.h"

int parse_input(char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_eat = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
	 	data->number_of_times_each_philosopher_must_eat = -1;
	return (1);
}


int main(int argc, char **argv)
{
	t_data data;

	data.number_of_times_each_philosopher_must_eat = 0;

	if(argc < 5)
	{
		//Provide meaningful error and 
		clean_error("Wrong arguments passed\n");
		return (1);
	}

	//Parse the arguments
	if (!parse_input(argv, &data))
		return (1);
	init_philo(&data);

	if (data.number_of_philosophers <= 1)
	{
		clean_error("Wrong arguments passed\n");
		return (1);
	}
	else if (data.number_of_philosophers == 1)
	{
		//TODO
	}
	start_dinner(&data);

}
