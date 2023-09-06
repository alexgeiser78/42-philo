#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>

typedef struct l_philo
{
	pthread_t		thread;
}	t_philo;

typedef struct l_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philo;
	pthread_mutex_t	essai;
}	t_info;

int	var_init(t_info *data, char *argv[]);

#endif