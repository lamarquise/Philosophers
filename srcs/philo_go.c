/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_go.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:01:04 by me                #+#    #+#             */
/*   Updated: 2021/12/16 00:32:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// different name?

#include "philosophers.h"

	// ok what that fuck the philo suposed to do...
// well for starters some of them wait before trying to take a fork
	// the odd or even ones, pick
// Then they need to try to grab a fork




// The thread that the Philos run
void	*ft_philo_go(void *arg)
{
	t_philo	*boi;	// as in iss ma boi

	boi = (t_philo *)arg;

	if (boi->id % 2 == 0)
		usleep(100);
	while (some shit)
	{
		// do some philosophizing...

		pthread_mutex_lock(&boi->l_fork);
		// print he got a fork
		pthread_mutex_lock(boi->r_fork);	// like this to dereference?
		// print he got a fork
		// set time when this philo ate
			// should this func use a mutex? that guy seems to think so...
			// looks that what, should i do the mutex here or in the function i call?
		// print he is eating
		// wait time instructed
			// the wait could be done in the print func!
		// print sleeping
		// unlock forks
		// print thinking
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
}

// The thread that checks if a philo is dead...
	// a thread func
void	*ft_check_if_dead(void *arg)
{
	t_ph	*all;

	all = arg;



}

