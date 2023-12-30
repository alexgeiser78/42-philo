/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:09:05 by ageiser           #+#    #+#             */
/*   Updated: 2023/12/06 18:09:08 by ageiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h> // gettimeofday
# include <unistd.h> // usleep
# include <limits.h> // INT_MAX

typedef struct l_philo
{
	int				id;// id of the philo
	int				meal_count;
	pthread_t		thread; // stores the thread id of the thread created
	long int		last_meal; // timestamp of the start of the last meal
	struct l_info	*info; // pointer to the struct info
	pthread_mutex_t	fork_l;	// pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_t	*fork_r; // pointer to mutex of the fork_l
}	t_philo;

typedef struct l_info
{
	int				time_to_die; // time to die after last meal
	int				num_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals; // number of meals till the game ends
	long int		start; // ms since epoch till the process started
	int				philo_eat; // common counter for all philos
	int				stop; // if other than 0, philo is dead
	t_philo			*philo; //malloc created for each philo
	pthread_mutex_t	print; // pthread_mutex_lock(&philo->info->print);
	pthread_mutex_t	meal_stop; // pthread_mutex_lock(&philo->info->meal_stop);
	pthread_mutex_t	meal_eat; // pthread_mutex_lock(&philo->info->meal_eat);
	pthread_mutex_t	dead; // pthread_mutex_lock(&philo->info->dead);
	pthread_mutex_t essai;
}	t_info;

int			check_num(char **str);
int			var_init(t_info *data, char *argv[]);
int			philo_run(t_info *data);
long long	timestamp(void);
void		*philo_life(void *phi_struct);
int			ft_atoi(const char *str); //libft
int			ft_isdigit(int c); //libft
int			is_dead(t_philo *philo, int nb);
void		ft_usleep(int ms);
void		print(t_philo *philo, char *str);
void		struct_init(t_info *data, int i);
int			join_thread(t_info *data, int i);


#endif
