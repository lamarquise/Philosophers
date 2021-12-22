/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:33:10 by me                #+#    #+#             */
/*   Updated: 2021/12/22 03:05:35 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_all_settings(t_ph *all)
{
	int	i;

	printf("--- Print All iSettings\n");
	if (!all)
		return (0);
	i = 0;
	while (i < 5)
	{
		ft_putnbrnl(all->iset[i]);
		++i;
	}
	printf("all start time: %ld\n", all->start_time);
	printf("--- DONE Print All iSettings\n");
	return (1);
}

int	ft_print_all_philos(t_ph *all)
{
	int	i;

	i = 0;
	while (i < all->iset[NPHILO])
	{
		ft_putstr("Last ate: ");
		ft_putlongnl(all->philos[i].last_ate);
		++i;
	}
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

int	ft_print_philo_status(t_philo *boi, int msg)
{
	long int		cur_time;

	if (ft_check_continue(boi) == 0)
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
	else if (msg == DIED)
		ft_putstr(" died\n");
	pthread_mutex_unlock(&boi->home->write_lock);
	return (1);
}
