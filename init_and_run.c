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

int	philo_run(t_info *data)
{
	int	i;

	data->start = timestamp();
	printf("data->start = %ldms\n\n", data->start); //
	i = -1;
	while (++i < data->num_of_philo)
	{
		printf("while %d < data->num_of_philo %d\n\n", i, data->num_of_philo); //
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].meal_count = 0;
		printf("data->philo[%d].id = %d\n",i, data->philo[i].id); //
		printf("data->philo[%d].last_meal = %ld\n",i, data->philo[i].last_meal); //
		printf("data->philo[%d].fork_r = %p\n",i, data->philo[i].fork_r); //
		printf("data->philo[%d].info = %p\n",i, data->philo[i].info); //
		printf("data->philo[%d].meal_count = %d\n",i, data->philo[i].meal_count); //
		printf("data in malloc %d = %p\n", data->philo[i].id, data); //
		pthread_mutex_init(&(data->philo[i].fork_l), NULL); // theorie de la fourchette gauche
		printf("mutex data->philo[%d].fork_l initialised\n", i); //
		if (i == data->num_of_philo -1)
			{
			printf("last philo\n"); //
			data->philo[i].fork_r = &data->philo[0].fork_l;
			printf("data->philo[%d].fork_r = %p\n",i, data->philo[i].fork_r); // theorie de la fourchette 0
			}	
		else
			{
			printf("not the last philo\n"); //
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
			printf("data->philo[%d].fork_r = data->philo[%d + 1].fork_l\n",i, i); //theorie de la fourchette  + 1
			}
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
					{
					printf("pthread_create error\n"); //
					return (-1);
					}
		else
			printf("pthread_create success\n"); //
	}
	printf("end of while\n\n"); //
	i = -1;
	while (++i < data->num_of_philo)
	{
		printf("pthread_join data->philo[%d].thread\n\n", i); //
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	}
	return (0);
}

//pthread_create() create a new thread.
//If attr is NULL, the default attributes are used. 
//Upon successful completion, pthread_create() stores the ID of 
//the created thread in the location referenced by thread.

//start_routine (&philo_life)

//The signal state of the new thread is initialised as follows:
//The signal mask is inherited from the creating thread.

//pthread_join() waits for the thread specified by thread to terminate.




int	var_init(t_info *data, char *argv[])
{	
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_stop, NULL);
	pthread_mutex_init(&data->meal_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	printf("4 mutex created\n"); //

	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	printf("malloc created for each philo\n"); //
	if (!data->philo)
		return (1);
	data->stop = 0;
	data->philo_eat = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] && data->num_of_meals == 0)
	{
		printf("num_of_meals = 0\n");
		return (1);
	}
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	printf("args into struct\n"); //
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
