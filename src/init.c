#include "../include/philo.h"
#include "../libft/libft.h"

int	var_init(t_info *data, char *argv[])
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}
