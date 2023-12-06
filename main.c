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
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
}
//pthread_mutex_destroy() function destroys the mutex object referenced by mutex
//If successful, pthread_mutex_init() and pthread_mutex_destroy return zero.
//Otherwise, an error number is returned to indicate the error.

int	main(int argc, char *argv[])
{
	t_info	data;

	if (argc != 5 && argc != 6)
		return (0);
	if (var_init(&data, argv) == 1)
	{
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	freeall(&data);
}
//data.philo = malloc created for each philo
