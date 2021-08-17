/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:13:27 by ericlazo          #+#    #+#             */
/*   Updated: 2021/08/17 22:15:45 by ericlazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// some useful generic Includes

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

	// it isn't allowed...
//#include "libft.h"

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
	pthread			id_thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	
	// i don't want to point back to the iset args nor do i want them
	// each to have their own copy...
	// I want them only to know what they need to know...
	// I will if i have to tho, like minilibx....

}				t_philo;


typedef struct s_ph
{
	t_philo	*philos;

	int		iset[5];

	pthread_mutext_t	write_lock;
	
	// some mutexes... i think
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
