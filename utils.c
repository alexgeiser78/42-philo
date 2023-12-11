/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageiser <ageiser@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:11:37 by ageiser           #+#    #+#             */
/*   Updated: 2023/12/06 18:11:39 by ageiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
    //printf("timestamp = %ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000); //
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // multiply and divide by 1000 to get milliseconds
}

//gettimeofday() function gets the system's clock time
//and stores it in the timeval structure 
//pointed to by tv (tv_sec and tv_usec)
//tv_sec is the number of seconds since the Epoch,
//and tv_usec is the number of microseconds
//since the last second.
//Epoch is 00:00:00 UTC, January 1, 1970

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
        {
		usleep(ms); // / 10  retour du /10
        }
    printf("sleep %dms\n", ms); //
}
//usleep() function suspends execution of the calling thread

int	is_dead(t_philo *philo, int nb) // check what nb is
{
    printf("is_dead?\n");//
	pthread_mutex_lock(&philo->info->dead);
    printf("mutex philo->info->dead lock\n"); //
    printf("nb = %d\n", nb); //
    if (nb)
    {
		philo->info->stop = 1;
        printf("philo->info->stop = %d\n", philo->info->stop); //
    }
    if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		printf("phteard_mutex_unlock\n"); //
        return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

