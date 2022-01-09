/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:01:04 by me                #+#    #+#             */
/*   Updated: 2022/01/09 21:36:56 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_more_philo_thread(t_philo *boi)
{
	if (!boi)
		return (0);
	pthread_mutex_lock(boi->r_fork);
	ft_print_philo_status(boi, GOT_FORK);
	ft_print_philo_status(boi, EATING);
	msleep(boi->home, boi->home->iset[TTEAT]);
	pthread_mutex_unlock(&boi->l_fork);
	pthread_mutex_unlock(boi->r_fork);
	pthread_mutex_lock(&boi->check_l_ate);
	boi->last_ate = ft_time_rn(boi->home) - boi->home->start_time;
	pthread_mutex_unlock(&boi->check_l_ate);
	pthread_mutex_lock(&boi->check_t_eaten);
	++boi->times_eaten;
	pthread_mutex_unlock(&boi->check_t_eaten);
	ft_print_philo_status(boi, SLEEPING);
	msleep(boi->home, boi->home->iset[TTSLEEP]);
	ft_print_philo_status(boi, THINKING);
	return (1);
}

void	*ft_philo_thread(void *arg)
{
	t_philo	*boi;

	boi = (t_philo *)arg;
	if (boi->id % 2 == 0)
		usleep(200);
	while (ft_check_continue(boi) == 1)
	{
		pthread_mutex_lock(&boi->l_fork);
		ft_print_philo_status(boi, GOT_FORK);
		if (!boi->r_fork)
		{
			pthread_mutex_unlock(&boi->l_fork);
			msleep(boi->home, boi->home->iset[TTDIE] * 2);
			return (NULL);
		}
		if (!ft_more_philo_thread(boi))
		{
			pthread_mutex_unlock(&boi->l_fork);
			pthread_mutex_lock(&boi->home->write_lock);
			ft_putstr("A Philo Thread Failed\n");
			pthread_mutex_unlock(&boi->home->write_lock);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_more_all_good(t_ph *all, int i)
{
	if (!all)
		return (0);
	pthread_mutex_lock(&all->philos[i].check_l_ate);
	if (ft_time_rn(all) - all->start_time - all->philos[i].last_ate \
		> all->iset[TTDIE])
	{
		ft_print_dead(&all->philos[i]);
		pthread_mutex_unlock(&all->philos[i].check_l_ate);
		return (0);
	}
	pthread_mutex_unlock(&all->philos[i].check_l_ate);
	return (1);
}

int	ft_all_good(t_ph *all)
{
	int	i;
	int	full;

	if (!all)
		return (0);
	i = 0;
	full = 0;
	while (i < all->iset[0])
	{
		if (!ft_more_all_good(all, i))
			return (0);
		pthread_mutex_lock(&all->philos[i].check_t_eaten);
		if (all->iset[4] > 0 && all->philos[i].times_eaten == all->iset[NEAT])
			++full;
		pthread_mutex_unlock(&all->philos[i].check_t_eaten);
		++i;
	}
	if (full == all->iset[NPHILO])
		return (2);
	return (1);
}

void	*ft_death_thread(void *arg)
{
	t_ph	*all;

	all = (t_ph *)arg;
	while (all->good == 1)
	{
		pthread_mutex_lock(&all->check_good);
		all->good = ft_all_good(all);
		pthread_mutex_unlock(&all->check_good);
		usleep(100);
	}
	return (NULL);
}
