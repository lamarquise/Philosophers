/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:01:04 by me                #+#    #+#             */
/*   Updated: 2021/12/21 02:15:17 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// different name?

#include "philo.h"

	// am i happy with the way and places i use this?
int	ft_check_continue(t_philo *boi)
{
	if (!boi)
		return (0);
	pthread_mutex_lock(&boi->home->check_good);
	if (!boi->home->good)
	{
		pthread_mutex_unlock(&boi->home->check_good);
		return (0);
	}
	pthread_mutex_unlock(&boi->home->check_good);
	pthread_mutex_lock(&boi->check_t_eaten);
	if (boi->times_eaten == boi->home->iset[NEAT])
	{
		pthread_mutex_unlock(&boi->check_t_eaten);
		return (2);	// i don't use this yet, but might in printing...
	}
	pthread_mutex_unlock(&boi->check_t_eaten);
	return (1);
}

// The thread that the Philos run
void	*ft_philo_thread(void *arg)
{
	t_philo	*boi;	// as in iss ma boi

	boi = (t_philo *)arg;

		// should i add more clever logic to when the philos should grab forks?
	if (boi->id % 2 == 0)
		usleep(boi->home->iset[TTEAT] / 10);
//		usleep(100);



	// i could call a function that checks boi->home->good, and in that func
		// i protect it
		// then protect good in all other places i look for it
	// do i keep finished eating?
	while (ft_check_continue(boi) == 1)
	{

		// should these be in a dif order?
		pthread_mutex_lock(&boi->l_fork);
		pthread_mutex_lock(boi->r_fork);	// like this to dereference?
		ft_print_philo_status(boi, GOT_FORK);
		ft_print_philo_status(boi, GOT_FORK);
		ft_print_philo_status(boi, EATING);
		msleep(boi->home, boi->home->iset[TTEAT]);
			// the wait could be done in the print func!
				// why bother tho, more complicated...
		pthread_mutex_unlock(&boi->l_fork);
		pthread_mutex_unlock(boi->r_fork);
		boi->last_ate = ft_time_rn(boi->home) - boi->home->start_time;
		++boi->times_eaten;
		// set time when this philo ate
			// should this func use a mutex? that guy seems to think so...
			// looks that what, should i do the mutex here or in the function i call?

		
		ft_print_philo_status(boi, SLEEPING);
		msleep(boi->home, boi->home->iset[TTSLEEP]);
		ft_print_philo_status(boi, THINKING);

//		printf("made to end of  thread loop, id: %d\n", boi->id);



/*		if (boi->home->iset[NEAT] != -1 && boi->times_eaten == boi->home->iset[NEAT])
		{
			boi->finished_eating = 1;
		}
*/
	}


	pthread_mutex_lock(&boi->home->write_lock);
	printf("made it to end of PHILO THREAD, philo id: %d,  all->good = %d\n", boi->id, boi->home->good);
	pthread_mutex_unlock(&boi->home->write_lock);

	// maybe there's a return?
	// temporary to shut up the compiler
	return ((void *)boi);
	// could return (NULL);
}

int		ft_all_good(t_ph *all)
{
	int i;
	// not convinced this shit works properly...
	int	full;

	if (!all)
		return (0);
	i = 0;
	full = 0;
	while (i < all->iset[NPHILO])
	{
		// check this condition again, make sure it actually does what you want.
		pthread_mutex_lock(&all->philos[i].check_l_ate);
		if (ft_time_rn(all) - all->start_time - all->philos[i].last_ate > all->iset[TTDIE])
		{
			ft_print_philo_status(&all->philos[i], DIED);
			return (0);
		}
		pthread_mutex_unlock(&all->philos[i].check_l_ate);

	// is this or the other place i check if full redundant?
	// i Need to pick one or the other, which is most well suited?
		pthread_mutex_lock(&all->philos[i].check_t_eaten);
		if (all->iset[NEAT] > 0 && all->philos[i].times_eaten == all->iset[NEAT])
			++full;
		pthread_mutex_unlock(&all->philos[i].check_t_eaten);

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
	t_ph	*all;

	all = arg;
	// should i call this everytime a philo updates its status?
		// not sure how to do that...

	while (all->good)
	{
		// works but could put mutex call right before returns in func
			// would be slightly more optimized?
		// Do i need this mutex if i don't use mutexes anywher else?
		pthread_mutex_lock(&all->check_good);
		all->good = ft_all_good(all);
		pthread_mutex_unlock(&all->check_good);
		// i doubt this is where i would free stuff in the event of all->good = 0...
			// prolly above, in main or something...

		usleep(100);
	}

	pthread_mutex_lock(&all->write_lock);
	printf("made it to end of DEATH THREAD, all->good = %d\n", all->good);
	pthread_mutex_unlock(&all->write_lock);
	// to shut up the compiler, will figur out later
	return ((void *)all);
}



