/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:13:27 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/20 16:37:04 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// some useful generic Includes

	// printf is allowed :)
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

	// need it...
# include "minilib.h"


# define TOTALPS 0

# define NPHILO 0
# define TTDIE 1
# define TTEAT 2
# define TTSLEEP 3
# define NEAT 4

# define GOT_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct s_philo
{
	int				id;
	// not sure if this is necessary, but better safe than sorry, will test
	pthread_mutex_t	check_t_eaten;
	int				times_eaten;	// call it eat_counter?
	// might need a mutex too...
	int				finished_eating;
	pthread_mutex_t	check_l_ate;
	long int		last_ate;	// so this is time it last ate - start time

	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	// we could keep all forks in t_ph in a table and reference them from here
	// as pointers?
	
	pthread_t			death_thread;

	struct s_ph		*home;
}				t_philo;


typedef struct s_ph
{
	t_philo				*philos;	// will end up being a table of pointers to struct.
	int					iset[5];	// initial settings.
	pthread_mutex_t	write_lock;
	//	testing multi death threads
	pthread_t			death;

		// does it need to be protected by a mutex?
			// yes if you use multi death threads
		// no right? cuz only changed by death thread, read by others tho...
	pthread_mutex_t		check_good;
	int					good;	// a bool that be like yea no one has died yet
								// but also haven't reached everyone has eaten
								// the required amount.
	pthread_mutex_t		check_time;
	long int			start_time;
}				t_ph;



/*
	** Things i need in my structure **

all the mutexes? a table of them?
all the threads? a table of them?

the state of each philo


*/


// reorganize the order of these things.

/*
**		Parser
*/

int			ft_parser(char **av, t_ph *all);

/*
**		Time
*/

long int	ft_time_rn(void);
void		msleep(long int micro_sec);

/*
**		Init
*/

int			ft_init_all(t_ph *all);
int			ft_start(t_ph *all);

/*
**		Threads
*/

void		*ft_philo_thread(void *arg);
// maybe call end thread? cuz it also ends if none dead but ate enough... IDK
void		*ft_death_thread(void *arg);

/*
**		Printing
*/

int			ft_print_all_philos(t_ph *all);
void		ft_putlongnl(long int nbr);
void		ft_putlong(long int n);
int			ft_print_all_settings(t_ph *all);
int			ft_print_philo_status(t_philo *boi, int msg);

#endif
