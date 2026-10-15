/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 16:01:18 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/15 09:55:09 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (simulate_death(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (simulate_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_output(philo, "has taken a fork");
	return (0);
}

int	odd_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (simulate_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (simulate_death(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_output(philo, "has taken a fork");
	return (0);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1)
			% data->number_of_philos];
		i++;
	}
	return ;
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return (1);
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			destroy_failed_forks(data, i);
			return (1);
		}
		i++;
	}
	data->fork_mut = 1;
	return (0);
}
