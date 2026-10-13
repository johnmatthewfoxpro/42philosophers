/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 15:52:37 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/13 11:08:46 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	data_mutex_init(t_data *data)
{
	if (!pthread_mutex_init(&data->print_ok, NULL))
		data->print_mut = 1;
	if (!pthread_mutex_init(&data->dead_ok, NULL))
		data->dead_mut = 1;
	if (!pthread_mutex_init(&data->finished_ok, NULL))
		data->fin_mut = 1;
	if (data->print_mut && data->dead_mut && data->fin_mut)
		return (0);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_args(argc, argv))
		return (1);
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->no_to_eat = ft_atoi(argv[5]);
	else
		data->no_to_eat = -1;
	data->all_eaten = 0;
	data->dead = 0;
	data->sim_start = 0;
	data->philos = 0;
	data->fork_mut = 0;
	data->print_mut = 0;
	data->dead_mut = 0;
	data->fin_mut = 0;
	if (data_mutex_init(data))
	{
		clean(data);
		return (1);
	}
	return (0);
}
