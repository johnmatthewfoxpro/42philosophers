/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:23:21 by jfox              #+#    #+#             */
/*   Updated: 2026/10/15 15:00:29 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*even_philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!simulate_death(philo->data))
	{
		if (philo->id % 2 == 0)
			ft_usleep(1, philo->data);
		if (pickup_fork(philo))
			break ;
		if (eat(philo))
		{
			drop_fork(philo);
			break ;
		}
		drop_fork(philo);
		if (philosophize_this(philo))
			break ;
	}
	return (NULL);
}

static void	*odd_philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->data->number_of_philos % 2 == 0)
		ft_usleep(10, philo->data);
	while (!simulate_death(philo->data))
	{
		if (pickup_fork(philo))
			break ;
		if (eat(philo))
		{
			drop_fork(philo);
			break ;
		}
		drop_fork(philo);
		if (philosophize_this(philo))
			break ;
	}
	return (NULL);
}

int	determine_routine(t_data *data, int i)
{
	if (data->number_of_philos % 2 == 0)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				even_philo_routine, &data->philos[i]))
		{
			clean(data);
			return (1);
		}
	}
	else
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				odd_philo_routine, &data->philos[i]))
		{
			clean(data);
			return (1);
		}
	}
	return (0);
}
