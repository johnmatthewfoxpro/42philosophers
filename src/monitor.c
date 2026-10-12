/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 16:09:43 by jfox              #+#    #+#             */
/*   Updated: 2026/10/12 18:17:26 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulate_finished(t_data *data)
{
	int	finished;

	pthread_mutex_lock(&data->finished_ok);
	finished = data->all_eaten;
	pthread_mutex_unlock(&data->finished_ok);
	return (finished);
}

static void	all_finished(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (!full(&data->philos[i]))
			return ;
		i++;
	}
	pthread_mutex_lock(&data->finished_ok);
	data->all_eaten = 1;
	pthread_mutex_unlock(&data->finished_ok);
	return ;
}

int	simulate_death(t_data *data)
{
	int	death;

	pthread_mutex_lock(&data->dead_ok);
	death = data->dead;
	pthread_mutex_unlock(&data->dead_ok);
	return (death);
}

static void	death(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_ok);
	pthread_mutex_lock(&data->dead_ok);
	if (!data->dead)
	{
		data->dead = 1;
		printf("%zd %d died\n", get_time() - data->sim_start, philo->id);
	}
	pthread_mutex_unlock(&data->dead_ok);
	pthread_mutex_unlock(&data->print_ok);
	return ;
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	ssize_t	last_eat;

	data = (t_data *)arg;
	while (!simulate_death(data) && !simulate_finished(data))
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_ok);
			last_eat = data->philos[i].last_eat;
			pthread_mutex_unlock(&data->philos[i].meal_ok);
			if ((get_time() - last_eat) > data->time_to_die)
			{
				// printf("debug philo %d, last eat = %zd, now = %zd, elapsed = %zd\n", data->philos[i].id, last_eat, get_time(), get_time() - last_eat);
				death(&data->philos[i]);
				return (NULL);
			}
			i++;
		}
		all_finished(data);
		ft_usleep(1, data);
	}
	return (NULL);
}
