/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:18:36 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/15 12:12:25 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	full(t_philos *philo)
{
	int	eaten;

	if (philo->data->no_to_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_ok);
	eaten = philo->eaten;
	pthread_mutex_unlock(&philo->meal_ok);
	if (eaten >= philo->data->no_to_eat)
		return (1);
	return (0);
}

int	pickup_fork(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		if (even_forks(philo))
			return (1);
	}
	else
	{
		if (odd_forks(philo))
			return (1);
	}
	return (0);
}

int	eat(t_philos *philo)
{
	if (simulate_death(philo->data))
		return (1);
	pthread_mutex_lock(&philo->meal_ok);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->meal_ok);
	print_output(philo, "is eating");
	if (ft_usleep(philo->data->time_to_eat, philo->data))
		return (1);
	pthread_mutex_lock(&philo->meal_ok);
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->meal_ok);
	return (0);
}

void	drop_fork(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return ;
}

int	philosophize_this(t_philos *philo)
{
	print_output(philo, "is sleeping");
	if (ft_usleep(philo->data->time_to_sleep, philo->data))
		return (1);
	print_output(philo, "is thinking");
	if (ft_usleep(philo->data->time_to_eat - philo->data->time_to_sleep,
			philo->data))
		return (1);
	if (philo->data->number_of_philos % 2 == 0)
		ft_usleep(1, philo->data);
	usleep(500);
	return (0);
}
