/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 16:08:28 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/13 14:59:34 by jfox             ###   ########.fr       */
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

static void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!simulate_death(philo->data) && !simulate_finished(philo->data))
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

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitor, NULL);
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
	set_time(data);
	if (data->number_of_philos == 1)
	{
		single_philo(&data->philos[i]);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
		{
			clean(data);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, monitor_routine, data))
	{
		clean(data);
		return (1);
	}
	return (0);
}
