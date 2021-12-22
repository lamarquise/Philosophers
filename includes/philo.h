/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:13:27 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/22 04:39:14 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

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

typedef struct s_philo
{
	int				id;
	struct s_ph		*home;
	pthread_t		thread;
	pthread_mutex_t	check_t_eaten;
	int				times_eaten;
	pthread_mutex_t	check_l_ate;
	long int		last_ate;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}				t_philo;

typedef struct s_ph
{
	pthread_t			death;
	t_philo				*philos;
	int					iset[5];
	pthread_mutex_t		write_lock;
	pthread_mutex_t		check_good;
	int					good;
	pthread_mutex_t		check_time;
	long int			start_time;
}				t_ph;

/*
**		Main
*/

int			ft_free_all_philos(t_ph *all);
int			ft_free_ph_struct(t_ph *all);
int			ft_free_all(t_ph *all);

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
**		Threads
*/

int			ft_more_philo_thread(t_philo *boi);
void		*ft_philo_thread(void *arg);
int			ft_more_all_good(t_ph *all, int i);
int			ft_all_good(t_ph *all);
void		*ft_death_thread(void *arg);

/*
**		Printing
*/

void		ft_putlongnl(long int nbr);
void		ft_putlong(long int n);
int			ft_check_continue(t_philo *boi);
int			ft_print_all_settings(t_ph *all);
int			ft_print_philo_status(t_philo *boi, int msg);

#endif
