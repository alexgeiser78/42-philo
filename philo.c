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

void	*check_death(void *phi)
{
	t_philo	*philosofer;

	philosofer = (t_philo *)phi;

	printf("check_death mutexes meal_eat, meal stop locked during:\n"); //
	printf("ft_usleep = %d\n", philosofer->info->time_to_die + 1); //
	ft_usleep(philosofer->info->time_to_die + 1);
	pthread_mutex_lock(&philosofer->info->meal_eat);
	pthread_mutex_lock(&philosofer->info->meal_stop);

	if (!is_dead(philosofer, 0) && timestamp() - \
			philosofer->last_meal >= (long)(philosofer->info->time_to_die)) // check death
	{
		pthread_mutex_unlock(&philosofer->info->meal_eat);
		pthread_mutex_unlock(&philosofer->info->meal_stop);
		print(philosofer, " died\n");
		is_dead(philosofer, 1);
	}
	pthread_mutex_unlock(&philosofer->info->meal_eat);
	pthread_mutex_unlock(&philosofer->info->meal_stop);
	printf("check_death mutexes meal_eat, meal stop unlocked\n"); //
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print(philo, " has taken a fork\n");
	if (philo->info->num_of_philo == 1)
	{
		ft_usleep(philo->info->time_to_die * 2); // *2 to check 
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->meal_eat));
	philo->last_meal = timestamp();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->info->meal_eat));
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
	print(philo, " is thinking\n");
}


void	*philo_life(void *phi_struct)
{
	t_philo		*philosofer;
	pthread_t	t;       
	
	philosofer = (t_philo *)phi_struct;
	printf("philo %d\n", philosofer->id); //);  
	printf("philosofer id = %d p = %p\n", philosofer->id, philosofer); //
	if (philosofer->id % 2 == 0) // if philosofer id is paire
	{
		printf("philo id is pair he waits\n"); //
		ft_usleep(philosofer->info->time_to_eat); // / 10  or not ? because timestamp 10 x / ms
		printf("ft_usleep time to eat %d\n", philosofer->info->time_to_eat); //
	}
	else
		printf("philo id is impair\n"); //
	

	while (!is_dead(philosofer, 0)) // 0 = alive, 1 = dead
	{
		printf("new thread\n"); //
		pthread_create(&t, NULL, check_death, phi_struct);
		take_fork(philosofer);
		philo_eat(philosofer);
		pthread_detach(t);
		if (philosofer->meal_count == philosofer->info->num_of_meals)
		{
			pthread_mutex_lock(&philosofer->info->meal_stop);
			if (++philosofer->info->philo_eat == philosofer->info->num_of_philo)
			{
				pthread_mutex_unlock(&philosofer->info->meal_stop);
				is_dead(philosofer, 2);
			}
			pthread_mutex_unlock(&philosofer->info->meal_stop);
			return (NULL);
		}	
	}
	return (0);

}

//pthread detach() When a detached thread terminates, 
//its resources are released to the system without
//another thread to join with the terminated thread.
