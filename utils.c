#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void    ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
    {
        write(fd, s, 1);
        s++;
    }
}



static int	ft_pow( int base, int power)
{
	int	i;
	int	initial_base;

	initial_base = base;
	i = power;
	if (power == 0)
		return (1);
	while (i > 1)
	{
		base = base * initial_base;
		i--;
	}
	return (base);
}

long	ft_atoi(char *str)
{
	int		i;
	int		minus_count;
	char	nums[1024];
	int		nums_i;
	long		result;

	result = 0;
	nums_i = 0;
	i = 0;
	minus_count = 0;
	while (str[i] == '-' || str[i] == '+' || str[i] == ' ')
	{
		if (str[i++] == '-')
			minus_count++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		nums[nums_i++] = str[i++];
	nums[nums_i] = '\0';
	i = ft_strlen(nums) -1 ;
	nums_i = 0;
	while (i >= 0)
		result += (nums[nums_i++] - 48) * (ft_pow(10, i--));
	if (minus_count % 2 == 1)
		return (result - (result * 2));
	return (result);
}


int clean_error(char *message)
{
	ft_putstr_fd(message, 1);
	//free everything
	return (1);
}

void *safe_malloc(size_t size)
{
	void *result;

	result = malloc(size);
	if (result == NULL)
		clean_error("Error allocating memory!");
	return (result);
}

long gettime(t_time_code code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		clean_error("Error getting time of day!");	
	if (code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (code == MILLISECONDS)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (code == MICROSECONDS)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
	 	clean_error("Wrong input in gettime func!");

	return (1);
}

void precise_usleep(long usec, t_data *data)
{
	long start;
	long elapsed;
	long remaining;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (is_simulation_done(data))
			break;
		elapsed = gettime(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (gettime(MICROSECONDS) - start < usec);
	}
}
