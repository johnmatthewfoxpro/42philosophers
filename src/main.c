/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:45:19 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/12 14:01:01 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->number_of_philos);
	if (!data->philos)
		return (1);
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eaten = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		data->philos[i].meal_mut = 0;
		if (pthread_mutex_init(&data->philos[i].meal_ok, NULL))
			return (1);
		data->philos[i].meal_mut = 1;
		i++;
	}
	return (0);
}

static int	init_sim(t_data *data)
{
	if (init_philos(data))
	{
		clean(data);
		return (1);
	}
	if (init_forks(data))
	{
		clean(data);
		return (1);
	}
	assign_forks(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (0);
	if (init_data(&data, argc, argv))
		return (1);
	if (init_sim(&data))
		return (1);
	if (create_threads(&data))
		return (1);
	if (data.number_of_philos > 1)
		join_thread(&data);
	clean(&data);
	return (0);
}
