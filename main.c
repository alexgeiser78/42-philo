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
}
//pthread_mutex_destroy() destroys the mutex object
//If successful, pthread_mutex_init() and pthread_mutex_destroy return zero.

int	main(int argc, char *argv[])
{
	t_info	data;

	printf("argc = %d\n", argc); //
	if (argc != 5 && argc != 6)
{
	printf(" args: ./philo num_of_philo time_to_die time_to_eat time_to_sleep\n");
		return (0);
}
	if (var_init(&data, argv) == 1)
	{
		free(data.philo);
		return (0);
	}	
	philo_run(&data);
	freeall(&data);
}

//data.philo = malloc created for each philo
