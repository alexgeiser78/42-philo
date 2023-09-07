#include "philo.h"

int	var_init(t_info *data, char *argv[])
{
	pthread_mutex_init(&data->essai, NULL);

	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);

	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}

//pthread_mutex_init()initialises the mutex 
//referenced by mutex with attributes specified by attr. 
//If attr is NULL, the default mutex attributes are used
//the effect is the same as passing the address of a 
//default mutex attributes object. Upon successful initialisation, 
//the state of the mutex becomes initialised and unlocked. 
//pthread_mutex_destroy() function destroys the mutex object referenced by mutex
//If successful, pthread_mutex_init() and pthread_mutex_destroy return zero.
//Otherwise, an error number is returned to indicate the error.