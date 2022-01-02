/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:01:06 by ericlazo          #+#    #+#             */
/*   Updated: 2022/01/02 18:37:07 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// this shit will prolly be quite different...
/*
int	ft_free_all_philos(t_ph *all)
{
	int	i;

	if (!all)
		return (0);
	i = 0;
	while (i < all->iset[NPHILO])
	{
		pthread_mutex_destroy(&all->philos[i].l_fork);
		pthread_mutex_destroy(&all->philos[i].check_t_eaten);
		pthread_mutex_destroy(&all->philos[i].check_l_ate);
		all->philos[i].r_fork = NULL;
		all->philos[i].home = NULL;
		++i;
	}
	free(all->philos);
	return (1);
}

int	ft_free_ph_struct(t_ph *all)
{
	if (!all)
		return (0);
	pthread_mutex_destroy(&all->check_time);
	pthread_mutex_destroy(&all->check_good);
	pthread_mutex_destroy(&all->write_lock);
	return (1);
}

int	ft_free_all(t_ph *all)
{
	if (!all)
		return (0);
	ft_free_all_philos(all);
	ft_free_ph_struct(all);
	return (1);
}
*/

void	ft_kill_philos(t_ph *all)
{
	int	i;

	i = 0;
	while (i < all->iset[0])
	{
		kill(all->philos[i].pid, SIGKILL);
		++i;
	}
}


int	main(int ac, char **av)
{
	t_ph	all;

	if (ac == 5)
		all.iset[4] = -1;
	else if (ac != 6)
		return (ft_error_msg("Error: wrong number of args\n", 0));
	if (!ft_parser(&av[1], &all))
		return (0);
	if (!ft_init_all(&all))
		return (ft_error_msg("Error: Init\n", 0));
	if (!ft_start(&all))
	{
//		ft_free_all(&all);
		return (ft_error_msg("Error: Failed to create processes\n", 0));
	}
//	ft_free_all(&all);
	return (1);
}
