/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:33:10 by me                #+#    #+#             */
/*   Updated: 2022/01/09 21:33:52 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_continue(t_philo *boi)
{
	if (!boi)
		return (0);
	pthread_mutex_lock(&boi->home->check_good);
	if (boi->home->good == 0)
	{
		pthread_mutex_unlock(&boi->home->check_good);
		return (0);
	}
	pthread_mutex_unlock(&boi->home->check_good);
	pthread_mutex_lock(&boi->check_t_eaten);
	if (boi->times_eaten == boi->home->iset[4])
	{
		pthread_mutex_unlock(&boi->check_t_eaten);
		return (2);
	}
	pthread_mutex_unlock(&boi->check_t_eaten);
	return (1);
}

void	ft_putlongnl(long int nbr)
{
	ft_putlong(nbr);
	ft_putchar('\n');
}

void	ft_putlong(long int n)
{
	long long		nb;
	unsigned char	*ret;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putlong(nb / 10);
	ret = (unsigned char *)(nb % 10 + 48);
	write(1, &ret, 1);
}

int	ft_print_dead(t_philo *boi)
{
	long int		cur_time;

	if (!boi)
		return (0);
	cur_time = ft_time_rn(boi->home) - boi->home->start_time;
	pthread_mutex_lock(&boi->home->write_lock);
	ft_putlong(cur_time);
	ft_putstr(" Philo ");
	ft_putnbr(boi->id);
	ft_putstr(" died\n");
	pthread_mutex_unlock(&boi->home->write_lock);
	return (1);
}

int	ft_print_philo_status(t_philo *boi, int msg)
{
	long int		cur_time;

	if (!boi || ft_check_continue(boi) == 0)
		return (0);
	cur_time = ft_time_rn(boi->home) - boi->home->start_time;
	pthread_mutex_lock(&boi->home->write_lock);
	ft_putlong(cur_time);
	ft_putstr(" Philo ");
	ft_putnbr(boi->id);
	if (msg == GOT_FORK)
		ft_putstr(" has taken a fork\n");
	else if (msg == EATING)
		ft_putstr(" is eating\n");
	else if (msg == SLEEPING)
		ft_putstr(" is sleeping\n");
	else if (msg == THINKING)
		ft_putstr(" is thinking\n");
	pthread_mutex_unlock(&boi->home->write_lock);
	return (1);
}
