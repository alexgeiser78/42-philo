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
    printf("tv.tv_sec = %ld\n", tv.tv_sec); //
    printf("tv.tv_usec = %d\n", tv.tv_usec); //
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

//gettimeofday() function gets the system's clock time
//and stores it in the timeval structure 
//pointed to by tv (tv_sec and tv_usec)
//tv_sec is the number of seconds since the Epoch,
//and tv_usec is the number of microseconds
//since the last second.
//Epoch is 00:00:00 UTC, January 1, 1970

int	is_dead(t_philo *philo, int nb)
{
    printf("is_dead\n");//
    printf("%d", nb); //
    free(philo); //
    return(0);//
}
