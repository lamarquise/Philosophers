/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:16:03 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/22 04:24:14 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parser(char **av, t_ph *all)
{
	int	i;

	if (!av || !all)
		return (0);
	i = 0;
	while (av[i])
	{
		if (!ft_str_isdigit(av[i]))
			return (ft_error_msg("Error: args must be positive nums\n", 0));
		all->iset[i] = ft_atoi(av[i]);
		++i;
	}
	if (all->iset[4] == 0)
		return (ft_error_msg("The Philosophers have eaten 0 times.\n", 0));
	if (all->iset[0] > 200)
		return (ft_error_msg("Too many Philosophers.\n", 0));
	if (all->iset[1] < 50 || all->iset[2] < 50 || all->iset[3] < 50)
		return (ft_error_msg("Too little time.\n", 0));
	return (1);
}
