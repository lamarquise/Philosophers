/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:25:04 by me                #+#    #+#             */
/*   Updated: 2021/12/21 02:15:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// should init file be called start?
// should i have a separate start file?


// 	this should be in a differnt file...
int		ft_init_all(t_ph *all)
{
	int	i;

	if (!all)
		return (0);

//	printf("made it to start of init\n");
	// i need a bit init all the vars area
	all->good = 1;

		// is this the right place to put this?
		// i mean i could put it at the end of the init of all the philos
	all->start_time = ft_time_rn(all);

	pthread_mutex_init(&all->write_lock, NULL);
	pthread_mutex_init(&all->check_good, NULL);
	pthread_mutex_init(&all->check_time, NULL);
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->iset[NPHILO]);
	if (!all->philos)
		return (0);
	// i totally forgot about the forks, we may need to break this up
	
	i = 0;
	while (i < all->iset[NPHILO])
	{
		all->philos[i].id = i + 1;
		pthread_mutex_init(&all->philos[i].check_t_eaten, NULL);
			// no need to mutex protect since no threads running yet.
		all->philos[i].times_eaten = 0;
		all->philos[i].finished_eating = 0;
		//all->philos[i].last_ate = all->start_time;
		pthread_mutex_init(&all->philos[i].check_l_ate, NULL);
		all->philos[i].last_ate = 0;
		all->philos[i].home = all;
		pthread_mutex_init(&all->philos[i].l_fork, NULL);
		// if there can be only 1 philo this will crash? need to check if that's allowed.
		if (all->iset[NPHILO] == 1)
			all->philos[i].r_fork = NULL;
		else if (i + 1 == all->iset[NPHILO])
			all->philos[i].r_fork = &all->philos[0].l_fork;
		else
			all->philos[i].r_fork = &all->philos[i + 1].l_fork;
		++i;
	}
	return (1);
}

// maybe have a func that does normal stuff inside a mutex?

	// this should prolly be moved
int	ft_start(t_ph *all)
{
	int	i;

	if (!all)
		return (0);
	
	// is this the right place for this?
	// i mean it seems fine?
	pthread_create(&all->death, NULL, &ft_death_thread, (void *)all);

	i = 0;
	while (i < all->iset[NPHILO])
	{
		// i might need to send the specific philo instead of everything...
		pthread_create(&all->philos[i].thread, NULL, &ft_philo_thread, (void *)&all->philos[i]);
		++i;
	}
	// is this the right place for this?
	// prolly want a return from this..
	pthread_join(all->death, NULL);

	i = 0;
	while (i < all->iset[NPHILO])
	{
		// you need to sort out the return for this..
		// should this be in an if?
		pthread_join(all->philos[i].thread, NULL);
		++i;
	}
	return (1);
}




