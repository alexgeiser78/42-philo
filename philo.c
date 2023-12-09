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

void	*philo_life(void *phi)
{
	t_philo		*philosofer;
	//pthread_t	t;           
	printf("first thread\n"); //
	printf("philo_life\n"); //
	philosofer = (t_philo *)phi;
	printf("philosofer = %p\n", philosofer); //
	if (philosofer->id % 2 == 0) // if philosofer id is paire
	{
		printf("philo id is pair so:\n"); //
		ft_usleep(philosofer->info->time_to_eat); // normaly /10 but don't know why
		printf("ft_usleep\n"); //
	}
	while (!is_dead(philosofer, 0)) // 0 probably egual to the last philo
	{
	}
	return (0);
}
