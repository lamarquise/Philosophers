/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:33:10 by me                #+#    #+#             */
/*   Updated: 2021/12/17 04:27:25 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// almost certainly move this...
int		ft_print_all_settings(t_ph *all)
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
	return (1);
}

int		ft_print_all_philos(t_ph *all)
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
	// add these to lib?
void	ft_putlongnl(long int nbr)
{
	ft_putlong(nbr);
	ft_putchar('\n');
}

void	ft_putlong(long int n)
{
	long long			nb;
	unsigned char	*ret;

//	printf("putlong, long: %ld\n", n);
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

// print the outputs
// maybe print some error messages...

	// return an int?
int	ft_print_philo_status(t_philo *boi, int msg)
{
	// an int? it's a long int normally, do i need to anticipate it ever being a long
	// int? if so i need a special putnbr...
	long int		cur_time;
	// i'm guessing i have to lock a print mutex...

	pthread_mutex_lock(&boi->home->write_lock);
	// timestamp
	// philo id
	// message

	// so i could surround this with a mutex or do it directly in the func...
	cur_time = ft_time_rn() - boi->home->start_time;

	ft_putlong(cur_time);
	ft_putchar(' ');
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
		ft_putstr(" has died\n");
	pthread_mutex_unlock(&boi->home->write_lock);
	return (1);
}



