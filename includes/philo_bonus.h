/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:13:27 by ericlazo          #+#    #+#             */
/*   Updated: 2022/01/02 19:34:24 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// i think this is all i need?
# include <signal.h> // for kill
# include <semaphore.h>

# include "minilib.h"

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

# define INTMAX 2147483647

// i'm guessing all this stuff has to change...

typedef struct s_philo
{
	int				id;
	int				pid;
	struct s_ph		*home;
//	pthread_t		thread;
//	pthread_mutex_t	check_t_eaten;
	int				times_eaten;
//	pthread_mutex_t	check_l_ate;
	long int		last_ate;
//	pthread_mutex_t	*r_fork;
//	pthread_mutex_t	l_fork;
}				t_philo;

typedef struct s_ph
{
//	pthread_t			death;
	t_philo				*philos;
	int					iset[5];
	sem_t				*write_lock;	// using pointers cuz other people do...
	sem_t				*check_good;
	sem_t				*check_time;
	sem_t				*forks;
//	pthread_mutex_t		write_lock;
//	pthread_mutex_t		check_good;
	int					good;
//	pthread_mutex_t		check_time;
	long int			start_time;
}				t_ph;

/*
**		Main
*/

int			ft_free_all_philos(t_ph *all);
int			ft_free_ph_struct(t_ph *all);
int			ft_free_all(t_ph *all);

void		ft_kill_philos(t_ph *all);

/*
**		Parser
*/

int			ft_parser(char **av, t_ph *all);

/*
**		Time
*/

long int	ft_time_rn(t_ph *all);
void		msleep(t_ph *all, long int millisec);

/*
**		Init
*/

int			ft_more_init(t_ph *all);
int			ft_init_all(t_ph *all);
int			ft_start(t_ph *all);

/*
**		Processes
*/

int			ft_more_philo_process(t_philo *boi);
void		*ft_philo_process(void *arg);
int			ft_more_all_good(t_ph *all, int i);
int			ft_all_good(t_ph *all);
void		*ft_death_thread(void *arg);

/*
**		Printing
*/

void		ft_putlongnl(long int nbr);
void		ft_putlong(long int n);
int			ft_check_continue(t_philo *boi);
int			ft_print_dead(t_philo *boi);
int			ft_print_philo_status(t_philo *boi, int msg);

#endif
