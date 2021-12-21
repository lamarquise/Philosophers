/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:01:06 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/21 02:02:39 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ok what is our logic:
// we check if the inputs are good
// we initialize what needs to be initialized
	// mutex, malloc all that
// we start the check if dead thread first? set vars of philos to something neg
	// so it knows they don't exist yet?
// we start the philo threads
// And we let it run...


// will surely need a free.c but for now keeping it here

int		ft_free_all_philos(t_ph *all)
{
	int	i;

	i = 0;
	while (i < all->iset[NPHILO])
	{
		pthread_mutex_destroy(&all->philos[i].l_fork);
		pthread_mutex_destroy(&all->philos[i].check_t_eaten);
		pthread_mutex_destroy(&all->philos[i].check_l_ate);
		all->philos[i].r_fork = NULL;
		all->philos[i].home = NULL;
		++i;
	}
	free(all->philos);
	return (1);
}

int		ft_free_ph_struct(t_ph *all)
{
	pthread_mutex_destroy(&all->check_time);
	pthread_mutex_destroy(&all->check_good);
	pthread_mutex_destroy(&all->write_lock);

//	pthread_mutex_destroy(&all->end);

	return (1);
}


int		main(int ac, char **av)
{
//	int			i;
	t_ph		all;
	
	if (ac == 5)
		all.iset[4] = -1;
	else if (ac != 6)
		return (ft_error_msg("ERROR: Bad Arguments\n", 0));
		// use error_msg_fd?

	// gotta init the Threads (here or possibly below...)
		// ac too?
	// in theory nothing to free yet if fails.
	if (!ft_parser(&av[1], &all))
		return (ft_error_msg("ERROR: Parser Failed\n", 0));

		// does stuff need to be freed in case of error?
	if (!ft_init_all(&all))
		return (ft_error_msg("ERROR: INIT Failed\n", 0));


		// prolly secure and free and all that...
	ft_start(&all);

	printf("made it to end of MAIN\n");
//	i = ft_start(&all);
//	if (i > all.iset[0])	// means no philos died
//		printf("cool no one died\n");	// def change later

	ft_free_all_philos(&all);
	ft_free_ph_struct(&all);

	return (1);
}










