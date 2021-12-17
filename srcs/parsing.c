/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:16:03 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/17 03:32:41 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


	// may do initiallizing in here too
		// or maybe just settings... IDK yet
int		ft_parser(char **av, t_ph *all)
{
	int	i;

	if (!av || !all)
		return (0);
	i = 0;
	while (av[i])
	{
		// is this enough of a check?
		// Do i need to check if there is at least 2 philos? is 1 fine? like expected? to just let him die?
		// Yes 1 is ok
		// should i make sure all the times things are above say 50 milliseconds?
		// if number of times eat is 0 return directly and free what needs to be freed.
		// could have more specific messages...
		if (!ft_str_isdigit(av[i]))
			return (0);
		all->iset[i] = ft_atoi(av[i]);
		if (all->iset[i] <= 0)
			return (0);
		++i;
	}
	if (all->iset[NEAT] == 0)
		return (1);
	// more checks?

//	ft_print_all_settings(all);
	return (1);
}






