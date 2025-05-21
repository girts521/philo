#include "philo.h"

void set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mtx *mutex, bool *value)
{
	bool result;

	mutex_handle(mutex, LOCK);
	result = *value;
	mutex_handle(mutex, UNLOCK);

	return (result);
}

void set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool get_long(t_mtx *mutex, long *value)
{
	long result;

	mutex_handle(mutex, LOCK);
	result = *value;
	mutex_handle(mutex, UNLOCK);

	return (result);
}

bool is_simulation_done(t_data *data)
{
	return (get_bool(&data->data_mutex, &data->end_simulation));
}
