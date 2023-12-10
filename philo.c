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

	printf("check_death\n"); //
	philosofer = (t_philo *)phi;
	ft_usleep(philosofer->info->time_to_die + 1);
	printf("ft_usleep = %d\n", philosofer->info->time_to_die + 1); //
	pthread_mutex_lock(&philosofer->info->m_eat);
	printf("mutex info->m_eat lock\n"); //
	pthread_mutex_lock(&philosofer->info->m_stop);
	printf("mutex info->m_stop lock\n"); //
	if (!is_dead(philosofer, 0) && timestamp() - \
			philosofer->last_meal >= (long)(philosofer->info->time_to_die))
	{
		pthread_mutex_unlock(&philosofer->info->m_eat);
		pthread_mutex_unlock(&philosofer->info->m_stop);
		//print(philo, " died\n");
		is_dead(philosofer, 1);
	}
	pthread_mutex_unlock(&philosofer->info->m_eat);
	pthread_mutex_unlock(&philosofer->info->m_stop);
	return (NULL);
}

void	*philo_life(void *phi)
{
	t_philo		*philosofer;
	pthread_t	t;       
	printf("philo_life\n"); //    
	printf("first thread\n"); //
	philosofer = (t_philo *)phi;
	printf("philosofer = %p\n", philosofer); //
	if (philosofer->id % 2 == 0) // if philosofer id is paire
	{
		printf("philo id is pair he eats, so:\n"); //
		ft_usleep(philosofer->info->time_to_eat); // normaly /10 but don't know why
		printf("ft_usleep\n"); //
	}
	while (!is_dead(philosofer, 0)) // 0 probably egual to the last philo
	{
		printf("new thread\n"); //
		pthread_create(&t, NULL, check_death, phi);
		
		break;
	}
	return (0);
}
