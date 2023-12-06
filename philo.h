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

typedef struct l_philo
{
	int				id;// to check
	int				m_count; // to check what is this?
	bool			is_eating; // to check
	pthread_t		thread; //to check indentificateur de struct (nom du philo)
	long int		last_meal; // to check
	struct l_info	*info; // to check
	pthread_mutex_t	*fork_l;	// to check
	pthread_mutex_t	*fork_r;	// to check
}	t_philo;

typedef struct l_info
{
	int				num_of_philo;
	int				time_to_die; //temps avant de mourir apres le dernier repas ou temps total?
	int				time_to_eat; // to check (temps pour manger)
	int				time_to_sleep; // to check (temps pour dormir)
	int				num_of_meals; // to check (nombre de repas)
	int				philo_eat; // what is this?
	int				stop; // to check
	long int		t_start; // to check (hour of start)
	t_philo			*philo; //malloc created for each philo
	pthread_mutex_t	essai; // to remove
	pthread_mutex_t	print; // to check and remove
	pthread_mutex_t	m_stop; // what is this?
	pthread_mutex_t	m_eat; // what is this?
	pthread_mutex_t	dead; // what is this?
}	t_info;

int			var_init(t_info *data, char *argv[]);
long long	timestamp(void);
void		*philo_life(void *phi); //to check
int			ft_atoi(const char *str); //libft
int			ft_isdigit(int c); //libft
int			is_dead(t_philo *philo, int nb); //to check
int			philo_init(t_info *data);


#endif
