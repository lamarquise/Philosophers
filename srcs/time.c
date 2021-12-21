/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:08:07 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/21 02:15:20 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// maybe reanme to activity or doing stuff or something better...
#include "philo.h"

	// is a long int what i want?
	// returns current time in Milliseconds
long int	ft_time_rn(t_ph *all)
{
	long int		cur_time;
	struct timeval	sys_time;

	// may need to surround this with a mutex...
	pthread_mutex_lock(&all->check_time);
	if (gettimeofday(&sys_time, NULL) == -1)
	{
		pthread_mutex_unlock(&all->check_time);
		return (ft_error_msg("Error: failed to get system time\n", -1));
	}
	cur_time = (sys_time.tv_sec * 1000) + (sys_time.tv_usec / 1000);
//	printf("in getting time: %ld\n", cur_time);
	pthread_mutex_unlock(&all->check_time);	
	return (cur_time);
}


// a new better msleep
// wait am i sending micro seconds or miliseconds????
// and if it's miliseconds how is working?
void	msleep(t_ph *all, long int micro_sec)
{
	long int	start;

	start = ft_time_rn(all);
	while (ft_time_rn(all) - start < micro_sec)
		usleep(micro_sec / 10);

}

// an msleep() func, milliseconds sleep rather than usleep or sleep...
/*
void	msleep(long int micro_sec)
{
	// do i need anything else? a security?
	usleep(micro_sec * 1000);
}
*/








