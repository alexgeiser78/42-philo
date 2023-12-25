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
    //printf("is_dead?\n");//
	pthread_mutex_lock(&philo->info->dead);
    //printf("mutex philo->info->dead lock\n"); //
    //printf("dead = %d\n", nb); //
    if (nb)
    {
		philo->info->stop = 1;
        //printf("philo->info->stop = %d\n", philo->info->stop); //
    }
    if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		//printf("mutex philo->info->dead unlock\n"); //
        return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	//printf("mutex philo->info->dead unlock\n"); //
	return (0);
}

void	*check_death(void *phi_struct)
{
	t_philo	*philosofer;

	philosofer = (t_philo *)phi_struct;

	//printf("check_death mutexes meal_eat, meal stop locked during:\n"); //
	//printf("ft_usleep = %d\n", philosofer->info->time_to_die ); // +1
	
	ft_usleep(philosofer->info->time_to_die + 1); //
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
	//printf("check_death mutexes meal_eat, meal stop unlocked\n"); //
	return (NULL);
}

// time to die + 1 because life is full time to die 
//philo dies when the time to die is superior to the time of the last meal

void	take_fork(t_philo *philo)
{
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
	//pthread_mutex_lock(&(philo->fork_l));
	
	/*if (philo->info->num_of_philo == 1)
	{
		ft_usleep(philo->info->time_to_die * 2);
		return ;
	}*/
	//pthread_mutex_lock((philo->fork_r));
	
}

//if there is only one philo, he has one fork, he dies

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
	//pthread_t	death_checker;       
	
	philosofer = (t_philo *)phi_struct;
	//printf("philo %d\n", philosofer->id); //);  
	//printf("philosofer id = %d p = %p\n", philosofer->id, philosofer); //
	if (philosofer->id % 2 == 0)
	{
		//printf("philo id is pair he waits\n"); //
		ft_usleep(philosofer->info->time_to_eat);
		//printf("ft_usleep time to eat %d\n", philosofer->info->time_to_eat); //
	}
	//else
		//printf("philo id is impair\n"); //
	//pthread_create(&death_checker, NULL, check_death, phi_struct);
	//pthread_detach(death_checker);
	while (!is_dead(philosofer, 0)) // 0 = alive, 1 = dead
	{
		//printf("new thread\n"); //
		//pthread_create(&thread, NULL, check_death, phi_struct);
		take_fork(philosofer);
		philo_eat(philosofer);
		//pthread_detach(thread); 
		if (philosofer->meal_count == philosofer->info->num_of_meals)
		{
			pthread_mutex_lock(&philosofer->info->meal_stop);
			if (++philosofer->info->philo_eat == philosofer->info->num_of_philo)
			{
				//pthread_mutex_unlock(&philosofer->info->meal_stop);
				is_dead(philosofer, 1);
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

//philosofer->id % 2 == 0 id pair always eats in second

//while is not dead, we create threads checking is not dead,
//we take forks, we eat, we unlock forks, we sleep, we think