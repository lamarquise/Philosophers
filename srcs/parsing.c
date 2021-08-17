/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:16:03 by ericlazo          #+#    #+#             */
/*   Updated: 2021/08/17 22:15:43 by ericlazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// almost certainly move this...
int		ft_print_all_settings(t_philo *all)
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
	return (1);
}

	// may do initiallizing in here too
		// or maybe just settings... IDK yet
int		ft_parser(char **av, t_philo *all)
{
	int	i;

	if (!av || !all)
		return (0);
	i = 0;
	while (av[i + 1])
	{
		all->iset[i] = ft_atoi(av[i + 1]);
		if (all->iset[i] <= 0)
			return (0);
		++i;
	}
		// maybe redundant...
	if (i == 5 && all->iset[4] <= 0)
		return (0);
	// some checks
	// is anything negative?

//	ft_print_all_settings(all);
	return (1);
}


int		ft_init(t_ph *all)
{
	pthread_mutex_init(&all->write_lock, NULL);


	return (1);
}





