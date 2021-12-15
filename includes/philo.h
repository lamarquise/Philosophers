/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:13:27 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/16 00:32:23 by me               ###   ########.fr       */
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

	// might change name to like 
/*
typedef struct	s_settings
{

	int		num_philos;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		num_eat;
}				t_settings;
*/


# define TOTALPS 0

# define NPHILO 0
# define TTDIE 1
# define TTEAT 2
# define TTSLEEP 3
# define NEAT 4

typedef struct s_philo
{
	int				id;
	int				times_eaten;	// call it eat_counter?
	long int		last_ate;	// so this is time it last ate - start time

	// im gonna need some other stuff, like time of creation
	// time it ate...
	// should this be pthread_t?
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	// we could keep all forks in t_ph in a table and reference them from here
	// as pointers?
	
	// i don't want to point back to the iset args nor do i want them
	// each to have their own copy...
	// I want them only to know what they need to know...
	// I will if i have to tho, like minilibx....

	// temporarily adding this just in case...
	t_ph			*home;
}				t_philo;


typedef struct s_ph
{
	t_philo				*philos;	// will end up being a table of pointers to struct.
	int					iset[5];	// initial settings.
	pthread_mutext_t	write_lock;
	
	pthread_t			death;

	// prolly gonna need some other stuff, like start time..

	long int			start_time;
}				t_ph;



/*
	** Things i need in my structure **

all the mutexes? a table of them?
all the threads? a table of them?

the state of each philo





*/

/*
**		Parser
*/

int		ft_parser(char **av, t_philo *all);

	// def move to print file
int		ft_print_all_settings(t_philo *all);








#endif
