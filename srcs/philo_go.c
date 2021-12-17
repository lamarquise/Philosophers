/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_go.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:01:04 by me                #+#    #+#             */
/*   Updated: 2021/12/17 04:27:22 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// different name?

#include "philo.h"

	// ok what that fuck the philo suposed to do...
// well for starters some of them wait before trying to take a fork
	// the odd or even ones, pick
// Then they need to try to grab a fork




// The thread that the Philos run
void	*ft_philo_go(void *arg)
{
	t_philo	*boi;	// as in iss ma boi

	boi = (t_philo *)arg;

	pthread_mutex_lock(&boi->home->write_lock);
	printf("made into a philo thread, id: %d\n", boi->id);
	ft_print_all_philos(boi->home);
	pthread_mutex_unlock(&boi->home->write_lock);
	if (boi->id % 2 == 0)
		usleep(100);
	// ok i need a way to stop this, i'm guessing when one has died...
	while (boi->home->good)
	{
		// do some philosophizing...

		// should i add more clever logic to when the philos should grab forks?
		pthread_mutex_lock(&boi->l_fork);
		ft_print_philo_status(boi, GOT_FORK);
		pthread_mutex_lock(boi->r_fork);	// like this to dereference?
		ft_print_philo_status(boi, GOT_FORK);
		boi->last_ate = ft_time_rn() - boi->home->start_time;
		// set time when this philo ate
			// should this func use a mutex? that guy seems to think so...
			// looks that what, should i do the mutex here or in the function i call?
		ft_print_philo_status(boi, EATING);
		msleep(boi->home->iset[TTEAT]);
			// the wait could be done in the print func!
		++boi->times_eaten;
		ft_print_philo_status(boi, SLEEPING);
		msleep(boi->home->iset[TTSLEEP]);
		pthread_mutex_unlock(&boi->l_fork);
		pthread_mutex_unlock(boi->r_fork);
		ft_print_philo_status(boi, THINKING);
			// but no sleep you could in theory start eating imediately after.

	}
	// odd or even ones wait...
	// they try to grab a fork (mutex protec)
	// they print they got a fork
		// for each fork?
	// print is eating...
		// wait some..
		// thus the msleep() func!
	// unlock things when done eating
	// print is sleeping
		// wait some
	// do i first try to grab a fork or print thinking...

	// put all this shit in a loop that stops when one has died, so need a way to
		// know one has died, from any philo...
		// also stops if they ate enough times...

	// maybe there's a return?
	// temporary to shut up the compiler
	return ((void *)boi);
}

// The thread that checks if a philo is dead...
	// a thread func
void	*ft_check_if_dead(void *arg)
{
	int		i;
	int		full;
	t_ph	*all;

	all = arg;

	pthread_mutex_lock(&all->write_lock);
	printf("checking if anything is dead\n");
	ft_print_all_settings(all);
	ft_print_all_philos(all);
	pthread_mutex_unlock(&all->write_lock);
	// if one dies, print dead and set good to good.

	while (all->good)
	{
		full = 0;
		i = 0;
		while (i < all->iset[NPHILO])
		{
			// is there a mutex i need to lock here?
			if (all->philos[i].last_ate + all->iset[TTDIE] \
				<= ft_time_rn() - all->start_time)
			{
				all->good = 0;
				ft_print_philo_status(&all->philos[i], DIED);
				
			}
			if (all->iset[NEAT] > 0 && all->philos[i].times_eaten == all->iset[NEAT])
				++full;
			++i;
		}
		if (full == all->iset[NPHILO])
			all->good = 0;
		// basically it checks all philo and sees if they haven't eaten recenlty
		// enough
		// or that they have met the number of times eaten asked for.
			// i bet there are ways to optimize this shit...

		// remeber to mutex lock all the vars you check that philos can change.

		// prolly a usleep to make so it doesn't check all the time?
		// or i call it everytime a philo updates its status?
			// not sure how to do that...
		usleep(100);
	}


	// to shut up the compiler, will figur out later
	return ((void *)all);
}






