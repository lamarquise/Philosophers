/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:01:06 by ericlazo          #+#    #+#             */
/*   Updated: 2021/08/17 22:07:50 by ericlazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Entirely for testiing purposes
/*
void	*test_write(void *data)
{
	int	i;
	char	str[] = "hello world";
	pthread_mutex_t	*mut;

	mut = (pthread_mutex_t *)data;
	i = 0;
	pthread_mutex_lock(mut);
	while (str[i])
	{
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		++i;
	}
	pthread_mutex_unlock(mut);
	fprintf(stderr, "\n\nEND\n");

	pthread_exit(NULL);

}


int		ft_start(t_philo *all)
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_mutex_t	mutex;

	if (!all)
		return (0);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &test_write, (void*)&mutex);
	pthread_create(&t2, NULL, &test_write, (void*)&mutex);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);


	return (1);
}
*/


/*
	// Maybe i need to start by testing simpler...
void	*test_write(void *all)
{
	int		i;
//	t_philo	*a;

//	a = (t_philo *)all;

	i = 0;
	pthread_mutex_lock();
	while (i < 5)
	{
		printf("this is thread %d, printed %d times\n", *((int *)all), i);
		++i;
	}
	pthread_mutex_unlock(
	pthread_exit(NULL);
}
*/



// may completely change this or at least put in dif file, but testing
	// for now
	// Testing Threads to start...
	// i want to have 2 philos share a fork... and go back and forth
		// between eating, telling me what's up at the same time
int		ft_start(t_philo *all)
{
	int 		i;
	pthread_mutex_t	mutex;


	if (!all)
		return (0);
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * all->iset[NPHILO]);
	if (!philos)
		return (0);	
	while(i < all->iset[NPHILO])
	{
		pthread_create(&philos[i], NULL, &test_write, (void *)i);
		++i;
	}
//	printf("i after threads created: %d\n", i);
	i = 0;
//	--i;
	while (i < all->iset[NPHILO])
	{
		pthread_join(philos[i], NULL);
		++i;
	}
//	printf("i after threads joined: %d\n", i);
	return (i);
}


int		main(int ac, char **av)
{
	int			i;
	t_ph		all;
	
	if (ac == 5)
		all.iset[4] = -1;
	else if (ac != 6)
		return (ft_error_msg("ERROR: Bad Arguments\n", 0));


	// gotta init the Threads (here or possibly below...)
		// ac too?
	if (!ft_parser(av, &all))
		return (ft_error_msg("ERROR: Parser Failed\n", 0));

	if (!ft_init(&all))
		return (ft_error_msg("ERROR: INIT Failed\n", 0));
	i = ft_start(&all);
	if (i > all.iset[0])	// means no philos died
		printf("cool no one died\n");	// def change later



	return (1);
}










