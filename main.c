/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:07:53 by ageiser           #+#    #+#             */
/*   Updated: 2023/12/06 18:07:55 by ageiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_thread(t_info *data)
{
	int i;
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	}
	return (0);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	freeall(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_stop);
	pthread_mutex_destroy(&data->meal_eat);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->essai);
}
//pthread_mutex_destroy() destroys the mutex object
//If successful, pthread_mutex_init() and pthread_mutex_destroy return zero.

void	mutex_init(t_info *data)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_stop, NULL);
	pthread_mutex_init(&data->meal_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->essai, NULL);
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

int	main(int argc, char *argv[])
{
	t_info	data;

	if ((argc != 5 && argc != 6) || check_num(argv) == 1)
	{
		printf("wrong arg: ./philo n_phil t_die t_eat t_sleep (n_meal)\n");
		return (0);
	}
	mutex_init(&data);
	if (var_init(&data, argv) == 1)
	{
		free(data.philo);
		return (0);
	}
	if (philo_run(&data) != 0)
	{
		printf("thread error\n");
		freeall(&data);
		return (0);
	}
	freeall(&data);
	return (0);
}

//data.philo = malloc created for each philo
