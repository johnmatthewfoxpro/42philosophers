/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 16:08:28 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/15 14:24:01 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	single_philo(t_philos *philo)
{
	print_output(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	print_output(philo, "died");
	return ;
}

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return ;
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->number_of_philos == 1)
	{
		single_philo(&data->philos[i]);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		data->philos[i].last_eat = data->sim_start;
		if (determine_routine(data, i))
			return (1);
		i++;
	}
	while (1)
	{
		if (monitor(data))
			break ;
	}
	return (0);
}
