/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:07:16 by ageiser           #+#    #+#             */
/*   Updated: 2023/12/06 18:07:22 by ageiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_think(t_philo *philo, void *phi_struct)
{
	long long	ttl;

	if (philo->info->time_to_die <= philo->info->time_to_eat * 2 \
	|| philo->info->time_to_die <= philo->info->time_to_sleep * 2)
	{
		pthread_mutex_lock(&philo->info->essai);
		ttl = philo->last_meal + philo->info->time_to_die;
		while (timestamp() <= ttl)
		{
			if (check_death(phi_struct) == 0)
				ft_usleep(1);
			else
				break ;
		}
		pthread_mutex_unlock(&philo->info->essai);
	}
}

void	nb_meal(t_philo *philosofer)
{
	if (philosofer->meal_count == philosofer->info->num_of_meals)
	{
		pthread_mutex_lock(&philosofer->info->meal_stop);
		if (philosofer->info->philo_eat == philosofer->info->num_of_philo)
			is_dead(philosofer, 1);
		pthread_mutex_unlock(&philosofer->info->meal_stop);
	}
}

void	struct_init(t_info *data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].last_meal = timestamp();
	data->philo[i].fork_r = NULL;
	data->philo[i].info = data;
	data->philo[i].meal_count = 0;
}

//pthread_join() waits for the thread specified by thread to terminate.

int	philo_run(t_info *data)
{
	int	i;

	data->start = timestamp();
	i = -1;
	while (++i < data->num_of_philo)
	{
		struct_init(data, i);
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->num_of_philo -1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	join_thread(data);
	return (0);
}

//pthread_create() create a new thread.
//If attr is NULL, the default attributes are used. 
//Upon successful completion, pthread_create() stores the ID of 
//the created thread in the location referenced by thread.

//start_routine (&philo_life)

//mutex data->philo[%d].fork_l is not a pointer 
//data->philo[i].fork_r pointer to mutex

int	var_init(t_info *data, char *argv[])
{
	data->stop = 0;
	data->philo_eat = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
	if (argv[5] && data->num_of_meals == 0)
	{
		printf("num_of_meals = 0\n");
		return (1);
	}
	return (0);
}

//mutex (from mutual exclusion) is a synchronization 
//primitive that prevents state from being modified 
//or accessed by multiple threads of execution at once

//pthread_mutex_init()initialises the mutex 
//referenced by mutex with attributes specified by attr. 
//If attr is NULL, the default mutex attributes are used
//the effect is the same as passing the address of a 
//default mutex attributes object. Upon successful initialisation, 
//the state of the mutex becomes initialised and unlocked. 
