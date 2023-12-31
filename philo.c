/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:08:49 by ageiser           #+#    #+#             */
/*   Updated: 2023/12/06 18:08:56 by ageiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int nb) // dead = 1, alive = 0
{
	pthread_mutex_lock(&philo->info->dead);
	if (philo->info->stop == 1)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	if (nb == 1)
	{
		philo->info->stop = 1;
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

int	check_death(void *phi_struct)
{
	t_philo	*philosofer;

	philosofer = (t_philo *)phi_struct;
	pthread_mutex_lock(&philosofer->info->meal_eat);
	pthread_mutex_lock(&philosofer->info->meal_stop);
	if (timestamp() - \
			philosofer->last_meal >= (long)(philosofer->info->time_to_die))
	{
		print(philosofer, " died\n");
		pthread_mutex_unlock(&philosofer->info->meal_eat);
		pthread_mutex_unlock(&philosofer->info->meal_stop);
		is_dead(philosofer, 1);
		return (1);
	}
	pthread_mutex_unlock(&philosofer->info->meal_eat);
	pthread_mutex_unlock(&philosofer->info->meal_stop);
	return (0);
}

// time to die + 1 because life is full time to die 
//philo dies when the time to die is superior to the time of the last meal

int	take_fork(t_philo *philosofer)
{
	pthread_mutex_lock(&(philosofer->fork_l));
	print(philosofer, " has taken a fork\n");
	if (philosofer->info->num_of_philo == 1)
	{
		ft_usleep(philosofer->info->time_to_die + 1);
		print(philosofer, "dies\n");
		is_dead(philosofer, 1);
		pthread_mutex_unlock(&(philosofer->fork_l));
		return (1);
	}
	pthread_mutex_lock((philosofer->fork_r));
	print(philosofer, " has taken a fork\n");
	return (0);
}

//if there is only one philo, he has one fork, he dies

void	philo_eat(t_philo *philo, void *phi_struct)
{
	long long	tte;
	long long	tts;

	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->meal_eat));
	philo->last_meal = timestamp();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->info->meal_eat));
	tte = timestamp() + philo->info->time_to_eat;
	while (timestamp() <= tte)
	{
		check_death(phi_struct);
		ft_usleep(1);
	}
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	tts = timestamp() + philo->info->time_to_sleep;
	while (timestamp() <= tts)
	{
		check_death(phi_struct);
		ft_usleep(1);
	}
	print(philo, " is thinking\n");
	time_to_think(philo, phi_struct);
}

void	*philo_life(void *phi_struct)
{
	t_philo		*philosofer;

	philosofer = (t_philo *)phi_struct;
	if (philosofer->id % 2 == 0)
		ft_usleep(philosofer->info->time_to_eat);
	while (is_dead(philosofer, 0) == 0 && \
	philosofer->meal_count != philosofer->info->num_of_meals)
	{
		if (take_fork(philosofer) == 0)
		{
			if (is_dead(philosofer, check_death(phi_struct)) == 0)
				philo_eat(philosofer, phi_struct);
			if (is_dead(philosofer, 0) == 1)
			{
				pthread_mutex_unlock(&philosofer->info->essai);
				break ;
			}
		}
	}
	nb_meal(philosofer);
	return (0);
}

//pthread detach() When a detached thread terminates, 
//its resources are released to the system without
//another thread to join with the terminated thread.

//philosofer->id % 2 == 0 id pair always eats in second

//while is not dead, we create threads checking is not dead,
//we take forks, we eat, we unlock forks, we sleep, we think