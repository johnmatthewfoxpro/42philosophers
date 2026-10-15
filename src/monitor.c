/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 16:09:43 by jfox              #+#    #+#             */
/*   Updated: 2026/10/15 13:33:40 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_finished(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (!full(&data->philos[i]))
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->finished_ok);
	data->end = 1;
	pthread_mutex_unlock(&data->finished_ok);
	return (1);
}

void	death(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->print_ok);
	pthread_mutex_lock(&philo->data->finished_ok);
	if (!philo->data->end)
	{
		philo->data->end = 1;
		printf("%zd %d died\n", get_time() - philo->data->sim_start, philo->id);
	}
	pthread_mutex_unlock(&philo->data->finished_ok);
	pthread_mutex_unlock(&philo->data->print_ok);
	return ;
}

int	simulate_death(t_data *data)
{
	int	death;

	pthread_mutex_lock(&data->finished_ok);
	death = data->end;
	pthread_mutex_unlock(&data->finished_ok);
	return (death);
}

int	check_death(t_data *data)
{
	int		i;
	ssize_t	last_eat;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_ok);
		last_eat = data->philos[i].last_eat;
		pthread_mutex_unlock(&data->philos[i].meal_ok);
		if ((get_time() - last_eat) >= data->time_to_die)
		{
			death(&data->philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor(t_data *data)
{
	if (check_death(data))
		return (1);
	if (all_finished(data))
		return (1);
	usleep(500);
	return (0);
}
