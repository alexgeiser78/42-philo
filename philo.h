#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>

typedef struct l_philo
{
	pthread_t		thread; //indentificateur de struct (nom du philo)
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

int		var_init(t_info *data, char *argv[]);
void	go(t_info data);
void	*philo_life(void *phi);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		is_dead(t_philo *philo, int nb);

#endif