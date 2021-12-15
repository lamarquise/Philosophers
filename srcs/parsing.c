/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:16:03 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/15 16:07:20 by erlazo           ###   ########.fr       */
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
	while (av[i])
	{
		// is this enough of a check?
		// Do i need to check if there is at least 2 philos? is 1 fine? like expected? to just let him die?
		// could have more specific messages...
		if (!ft_str_isdigit(av[i]))
			return (0);
		all->iset[i] = ft_atoi(av[i]);
		if (all->iset[i] <= 0)
			return (0);
		++i;
	}
	// more checks?

//	ft_print_all_settings(all);
	return (1);
}


// 	this should be in a differnt file...
int		ft_init(t_ph *all)
{
	int	i;

//	pthread_mutex_init(&all->write_lock, NULL);

	// Do i need to start another thread first?

	i = 0;
	if (!all)
		return (0);
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->iset[NPHILO]);
	if (!all->philos)
		return (0);
	// i totally forgot about the forks, we may need to break this up
	
	while (i < all->iset[NPHILO])
	{
		all->philos[i]->id = i + 1;
		pthread_mutex_init(&all->philos[i]->l_fork, NULL);
		// if there can be only 1 philo this will crash? need to check if that's allowed.
		if (i + 1 == all->iset[NPHILO])
			all->philos[i]->r_fork = all->philos[0]->l_fork;
		else
			all->philos[i]->r_fork = all->philos[i + 1]->l_fork;
		pthread_create(&all->philos[i]->thread, NULL, &ft_philo_go, (void *)all);
		++i;
	}

	// maybe this part does belong is "ft_start" or something...
	i = 0;
	while (i < all->iset[NPHILO])
	{
		// might want a place to get a return from this...
		pthread_join(all->philos[i]->thread, NULL);

		++i;
	}

	return (1);
}


// obivously move this but here for now
// The thread that checks if a philo is dead...
	// a thread func
void	*ft_check_if_dead(void *arg)
{
	t_ph	*all;

	all = arg;



}









