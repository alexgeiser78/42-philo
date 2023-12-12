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
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h> //usleep
# include <limits.h> //INT_MAX

typedef struct l_philo
{
	int				id;// id of the philo
	int				meal_count; // to check
	bool			is_eating; // to check
	pthread_t		thread; // stores the thread id of the thread created
	long int		last_meal; // to check
	struct l_info	*info; // pointer to the struct info
	pthread_mutex_t	fork_l;	// to check
	pthread_mutex_t	*fork_r;	// to check
}	t_philo;

typedef struct l_info
{
	int				num_of_philo;
	int				time_to_die; // time to die after last meal
	int				time_to_eat; 
	int				time_to_sleep;
	int				num_of_meals; // number of meals till the game ends
	long int		start; // ms since epoch
	int				philo_eat; // what is this?
	int				stop; // to check
	t_philo			*philo; //malloc created for each philo
	pthread_mutex_t	essai; // to remove
	pthread_mutex_t	print; // to check and remove
	pthread_mutex_t	meal_stop; // to check 
	pthread_mutex_t	meal_eat; // what is this?
	pthread_mutex_t	dead; // pthread_mutex_lock(&philo->info->dead);
}	t_info;

int			check_num(char **str);
int			var_init(t_info *data, char *argv[]);
int			philo_init(t_info *data);
long long	timestamp(void);
void		*philo_life(void *phi); //to check
int			ft_atoi(const char *str); //libft
int			ft_isdigit(int c); //libft
int			is_dead(t_philo *philo, int nb); //to check
void		ft_usleep(int ms);
void		print(t_philo *philo, char *str); //to check


#endif
