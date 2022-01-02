/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:25:04 by me                #+#    #+#             */
/*   Updated: 2022/01/02 19:34:17 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_more_init(t_ph *all)
{
	int	i;

	if (!all)
		return (0);
	i = 0;
	while (i < all->iset[0])
	{
		all->philos[i].id = i + 1;
//		pthread_mutex_init(&all->philos[i].check_t_eaten, NULL);
		all->philos[i].times_eaten = 0;
//		pthread_mutex_init(&all->philos[i].check_l_ate, NULL);
		all->philos[i].last_ate = 0;
		all->philos[i].home = all;
//		pthread_mutex_init(&all->philos[i].l_fork, NULL);
/*		if (all->iset[NPHILO] == 1)
			all->philos[i].r_fork = NULL;
		else if (i + 1 == all->iset[NPHILO])
			all->philos[i].r_fork = &all->philos[0].l_fork;
		else
			all->philos[i].r_fork = &all->philos[i + 1].l_fork;
*/
		++i;
	}
	return (1);
}

int	ft_init_all(t_ph *all)
{
	if (!all)
		return (0);
	all->good = 1;
	all->start_time = ft_time_rn(all);
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->iset[NPHILO]);
	if (!all->philos)
		return (0);

	// init some semaphores
	sem_unlink("/sem_write_lock");	// i guess adding sem_ is a convention?
	sem_unlink("/sem_check_good");
	sem_unlink("/sem_check_time");
	sem_unlink("/sem_forks");
	all->write_lock = sem_open("/sem_write_lock", O_CREAT | O_EXCL, 0644, 1);
	all->check_good = sem_open("/sem_check_good", O_CREAT | O_EXCL, 0644, 1);
	all->check_time = sem_open("/sem_check_time", O_CREAT | O_EXCL, 0644, 1);
	all->forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 0644, all->iset[0]);
	// prolly want a check to see if the sem creation worked properly
	// some sort of if

	ft_more_init(all);
/*	pthread_mutex_init(&all->write_lock, NULL);
	pthread_mutex_init(&all->check_good, NULL);
	pthread_mutex_init(&all->check_time, NULL);
	if (!ft_more_init(all))
	{
		free(all->philos);
		ft_free_ph_struct(all);
		return (0);
	}
*/
	return (1);
}

/*
	working out some logic

	id = fork()
	if (id == 0)
		philo proces()
	else 
		fork()?



*/



int	ft_start(t_ph *all)
{
	int	i;
	int	id;

	if (!all)
		return (0);

	// something about forks here...
	id = 1;
	i = 0;
//	while (i < all->iset[0])
	while (id > 0 && i < all->iset[0])
	{
	// don't do it like this
	// if fork id == 0 run a process
	// else fork again til we have enough
//		id = fork();

			id = fork();
		//	all->philos[i].pid = fork();
			all->philos[i].pid = id;
		if (all->philos[i].pid == -1)
			return (0);
		if (all->philos[i].pid == 0)
		{
			// start the philo.
			ft_philo_process(&all->philos[i]);
		}
		++i;
	}
	return (1);
}

/*
int	ft_start(t_ph *all)
{
	int	i;

	if (!all)
		return (0);
	if (pthread_create(&all->death, NULL, &ft_death_thread, (void *)all) != 0)
		return (0);
	i = 0;
	while (i < all->iset[0])
	{
		if (pthread_create(&all->philos[i].thread, NULL, \
			&ft_philo_thread, (void *)&all->philos[i]) != 0)
			return (0);
		++i;
	}
	pthread_join(all->death, NULL);
	i = 0;
	while (i < all->iset[0])
	{
		pthread_join(all->philos[i].thread, NULL);
		++i;
	}
	return (1);
}
*/
