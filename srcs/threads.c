/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:01:04 by me                #+#    #+#             */
/*   Updated: 2021/12/17 19:36:57 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// different name?

#include "philo.h"

	// ok what that fuck the philo suposed to do...
// well for starters some of them wait before trying to take a fork
	// the odd or even ones, pick
// Then they need to try to grab a fork




// The thread that the Philos run
void	*ft_philo_thread(void *arg)
{
	t_philo	*boi;	// as in iss ma boi

	boi = (t_philo *)arg;

//	pthread_mutex_lock(&boi->home->write_lock);
//	printf("made into a philo thread, id: %d\n", boi->id);
//	ft_print_all_philos(boi->home);
//	pthread_mutex_unlock(&boi->home->write_lock);
	if (boi->id % 2 == 0)
		usleep(100);


		// obviously this didn't work...
//	pthread_mutex_lock(&boi->home->end);

	// ok i need a way to stop this, i'm guessing when one has died...
	while (boi->home->good)
	{
		// do some philosophizing...

		// should i add more clever logic to when the philos should grab forks?
		// should these be in a dif order?
		pthread_mutex_lock(&boi->l_fork);
		pthread_mutex_lock(boi->r_fork);	// like this to dereference?
		ft_print_philo_status(boi, GOT_FORK);
		ft_print_philo_status(boi, GOT_FORK);
/*		if (!boi->home->good)
		{
			pthread_mutex_unlock(&boi->l_fork);
			pthread_mutex_unlock(boi->r_fork);
			return (0);
		}
*/
		ft_print_philo_status(boi, EATING);
		msleep(boi->home->iset[TTEAT]);
			// the wait could be done in the print func!
		// does this need to be mutex protected?
		pthread_mutex_unlock(&boi->l_fork);
		pthread_mutex_unlock(boi->r_fork);
		boi->last_ate = ft_time_rn() - boi->home->start_time;
		++boi->times_eaten;
		// set time when this philo ate
			// should this func use a mutex? that guy seems to think so...
			// looks that what, should i do the mutex here or in the function i call?

//		pthread_mutex_lock(&boi->home->write_lock);
//		printf("philo id: %d, last ate: %ld\n", boi->id, boi->last_ate);
//		ft_print_all_philos(boi->home);
//		pthread_mutex_unlock(&boi->home->write_lock);
		
		ft_print_philo_status(boi, SLEEPING);
		msleep(boi->home->iset[TTSLEEP]);
		ft_print_philo_status(boi, THINKING);
			// but no sleep you could in theory start eating imediately after.

	}
//	pthread_mutex_unlock(&boi->home->end);


	printf("made it to end of PHILO THREAD, philo id: %d,  all->good = %d\n", boi->id, boi->home->good);

	// maybe there's a return?
	// temporary to shut up the compiler
	return ((void *)boi);
}

// possibly tmp
int		ft_all_good(t_ph *all)
{
	int i;
	int	full;

	if (!all)
		return (0);
	i = 0;
	full = 0;
	while (i < all->iset[NPHILO])
	{
		// check this condition again, make sure it actually does what you want.
		if (ft_time_rn() - all->start_time - all->philos[i].last_ate > all->iset[TTDIE])
		{
			ft_print_philo_status(&all->philos[i], DIED);
			return (0);
		}
		if (all->iset[NEAT] > 0 && all->philos[i].times_eaten == all->iset[NEAT])
			++full;
		++i;
	}
	if (full == all->iset[NPHILO])
		return (0);
	return (1);
}



// The thread that checks if a philo is dead...
	// a thread func
void	*ft_death_thread(void *arg)
{
//	int		i;
//	int		full;
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
		// maybe i need a dif mutex for good or not!
//		pthread_mutex_lock(&all->end);
		all->good = ft_all_good(all);
//		pthread_mutex_unlock(&all->end);
		// i doubt this is where i would free stuff in the event of all->good = 0...
			// prolly above, in main or something...
/*
		full = 0;
		i = 0;
		while (i < all->iset[NPHILO])
		{
			// is there a mutex i need to lock here?
			// is a philo dead Check:
		//	if (all->philos[i].last_ate + all->iset[TTDIE] \
		//		<= ft_time_rn() - all->start_time)
			if (ft_time_rn() - all->start_time - all->philos[i].last_ate > all->iset[TTDIE])
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
*/



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

	printf("made it to end of DEATH THREAD, all->good = %d\n", all->good);
	// to shut up the compiler, will figur out later
	return ((void *)all);
}






