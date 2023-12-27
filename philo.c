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
	if (nb)
	{
		philo->info->stop = 1;
	}
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

void	*check_death(void *phi_struct)
{
	t_philo	*philosofer;

	philosofer = (t_philo *)phi_struct;
	pthread_mutex_lock(&philosofer->info->meal_eat);
	pthread_mutex_lock(&philosofer->info->meal_stop);
	if (!is_dead(philosofer, 0) && timestamp() - \
			philosofer->last_meal >= (long)(philosofer->info->time_to_die + 1))
	{
		print(philosofer, " died\n");
		is_dead(philosofer, 1);
	}
	pthread_mutex_unlock(&philosofer->info->meal_eat);
	pthread_mutex_unlock(&philosofer->info->meal_stop);
	return (NULL);
}

// time to die + 1 because life is full time to die 
//philo dies when the time to die is superior to the time of the last meal

void	take_fork(t_philo *philo)
{
	if (philo->info->num_of_philo == 1)
	{
		ft_usleep(philo->info->time_to_die * 2);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->fork_l));
		pthread_mutex_lock((philo->fork_r));
		print(philo, " has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock((philo->fork_r));
		pthread_mutex_lock(&(philo->fork_l));
		print(philo, " has taken a fork\n");
	}
}

//if there is only one philo, he has one fork, he dies

void	philo_eat(t_philo *philo)
{
	long long end_time;

	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->meal_eat));
	philo->last_meal = timestamp();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->info->meal_eat));
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	end_time = timestamp() + philo->info->time_to_sleep;
	while (timestamp() <= end_time)
		ft_usleep(1);
	print(philo, " is thinking\n");
}

void	*philo_life(void *phi_struct)
{
	t_philo		*philosofer;

	philosofer = (t_philo *)phi_struct;
	if (philosofer->id % 2 == 0)
		ft_usleep(philosofer->info->time_to_eat);
	while (!is_dead(philosofer, 0) && \
	philosofer->meal_count != philosofer->info->num_of_meals)
	{
		take_fork(philosofer);
		check_death(phi_struct);
		philo_eat(philosofer);
	}
	if (philosofer->meal_count == philosofer->info->num_of_meals)
	{
		pthread_mutex_lock(&philosofer->info->meal_stop);
		if (++philosofer->info->philo_eat == philosofer->info->num_of_philo)
		{
			is_dead(philosofer, 1);
		}
		pthread_mutex_unlock(&philosofer->info->meal_stop);
		return (NULL);
	}
	return (0);
}

//pthread detach() When a detached thread terminates, 
//its resources are released to the system without
//another thread to join with the terminated thread.

//philosofer->id % 2 == 0 id pair always eats in second

//while is not dead, we create threads checking is not dead,
//we take forks, we eat, we unlock forks, we sleep, we think