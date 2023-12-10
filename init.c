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

int	philo_init(t_info *data)
{
	int	i;

	data->start = timestamp();
	printf("start = %ldms\n", data->start); //
	i = 1;
	while (i <= data->num_of_philo)
	{
		printf("while %d <= data->num_of_philo %d\n", i, data->num_of_philo); //
		data->philo[i].id = i;
		data->philo[i].last_meal = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		printf("data->philo[%d].id = %d\n",i, data->philo[i].id); //
		printf("data->philo[%d].last_meal = %ld\n",i, data->philo[i].last_meal); //
		printf("data->philo[%d].fork_r = %p\n",i, data->philo[i].fork_r); //
		printf("data->philo[%d].info = %p\n",i, data->philo[i].info); //
		printf("data->philo[%d].m_count = %d\n",i, data->philo[i].m_count); //
		printf("data in malloc %d = %p\n", data->philo[i].id, data); //
		pthread_mutex_init(&(data->philo[i].fork_l), NULL); // remove & maybe
		if (i == data->num_of_philo)
			{
			printf("last philo\n"); //
			data->philo[i].fork_r = &data->philo[0].fork_l;
			printf("data->philo[%d].fork_r = %p\n",i, data->philo[i].fork_r); //
			}	
		else
			{
			printf("first philo\n"); //
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
			printf("data->philo[%d].fork_r = %p\n",i, data->philo[i].fork_r); //
			}
		printf("pthread_create\n"); //
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			
			return (-1);
		i++;
	}
	printf("end of while\n"); //
	i = 1;
	while (i < data->num_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}
//pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//    void *(*start_routine)(void*), void *arg);

//pthread_create() create a new thread, with attributes specified by attr
//If attr is NULL, the default attributes are used. 
//If the attributes specified by attr are modified later, the thread's attributes 
//are not affected. Upon successful completion, pthread_create() stores the ID of 
//the created thread in the location referenced by thread.

//start_routine with arg as its sole argument. If the start_routine returns, 
//the effect is as if there was an implicit call to pthread_exit() 
//using the return value of start_routine as the exit status. Note that 
//the thread in which main() was originally invoked differs from this. 
//When it returns from main(), the effect is as if there was an implicit 
//call to exit() using the return value of main() as the exit status.

//The signal state of the new thread is initialised as follows:
//The signal mask is inherited from the creating thread.
//The set of signals pending for the new thread is empty.
//If pthread_create() fails, no new thread is created and the contents of the 
//location referenced by thread are undefined. 

//RETURN VALUE

//If successful, the pthread_create() function returns zero. 
//Otherwise, an error number is returned to indicate the error. 




int	var_init(t_info *data, char *argv[])
{	
	pthread_mutex_init(&data->essai, NULL);//
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	printf("6 mutex created\n"); //
	data->stop = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	printf("malloc created for each philo\n"); //
	if (!data->philo)
		return (1);
	data->philo_eat = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	printf("args into struct\n"); //
	if (argv[5] && data->num_of_meals == 0)
		return (1);
	printf("check if argv[5] is 0 which can't be\n"); //
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
