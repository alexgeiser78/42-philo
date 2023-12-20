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
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// multiply and divide by 1000 to get milliseconds
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
		usleep(ms);
        }
    //printf("sleep %dms\n", ms); //
}
//usleep() function suspends execution of the calling thread

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	time = timestamp() - philo->info->start;
	if (!philo->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lldms id %d %s", timestamp() - philo->info->start, philo->id, str); // wow
	pthread_mutex_unlock(&(philo->info->print));
}

