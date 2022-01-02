/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:08:07 by ericlazo          #+#    #+#             */
/*   Updated: 2022/01/02 18:35:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	ft_time_rn(t_ph *all)
{
	long int		cur_time;
	struct timeval	sys_time;

	(void)all;
//	pthread_mutex_lock(&all->check_time);
	if (gettimeofday(&sys_time, NULL) == -1)
	{
//		pthread_mutex_unlock(&all->check_time);
		return (ft_error_msg("Error: failed to get system time\n", -1));
	}
	cur_time = (sys_time.tv_sec * 1000) + (sys_time.tv_usec / 1000);
//	pthread_mutex_unlock(&all->check_time);
	return (cur_time);
}

void	msleep(t_ph *all, long int millisec)
{
	long int	start;

	start = ft_time_rn(all);
	while (ft_time_rn(all) - start < millisec)
		usleep(millisec / 10);
}
