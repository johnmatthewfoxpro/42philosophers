/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:18:36 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/12 15:00:12 by jfox             ###   ########.fr       */
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
	printf("debug %zd philo %d wants forks \n", get_time() - philo->data->sim_start ,philo->id);
	if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        if (simulate_death(philo->data) || simulate_finished(philo->data))
        {
            pthread_mutex_unlock(philo->right_fork);
            return (1);
        }
        print_output(philo, "has taken a right fork");

        pthread_mutex_lock(philo->left_fork);
        if (simulate_death(philo->data) || simulate_finished(philo->data))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return (1);
        }
        print_output(philo, "has taken a left fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        if (simulate_death(philo->data) || simulate_finished(philo->data))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
        print_output(philo, "has taken a left fork");

        pthread_mutex_lock(philo->right_fork);
        if (simulate_death(philo->data) || simulate_finished(philo->data))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
        print_output(philo, "has taken a right fork");
    }
	printf("debug %zd philo %d has forks \n", get_time() - philo->data->sim_start ,philo->id);
    return (0);
}

int	eat(t_philos *philo)
{
	if (simulate_death(philo->data) || simulate_finished(philo->data))
		return (1);
	pthread_mutex_lock(&philo->meal_ok);
	philo->last_eat = get_time();
	printf("debug %zd philo %d starts eating\n", get_time() - philo->data->sim_start ,philo->id);
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->meal_ok);
	print_output(philo, "is eating");
	if (ft_usleep(philo->data->time_to_eat, philo->data))
		return (1);
	// pthread_mutex_lock(&philo->meal_ok);
	// philo->eaten += 1;
	// pthread_mutex_unlock(&philo->meal_ok);
	return (0);
}

void	drop_fork(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		print_output(philo, "has dropped a left fork");
		pthread_mutex_unlock(philo->right_fork);
		print_output(philo, "has dropped a right fork");
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		print_output(philo, "has dropped a right fork");
		pthread_mutex_unlock(philo->left_fork);
		print_output(philo, "has dropped a left fork");
	}
	return ;
}

int	philosophize_this(t_philos *philo)
{
	if (simulate_death(philo->data) || simulate_finished(philo->data))
		return (1);
	print_output(philo, "is sleeping");
	if (ft_usleep(philo->data->time_to_sleep, philo->data))
		return (1);
	if (simulate_death(philo->data) || simulate_finished(philo->data))
		return (1);
	print_output(philo, "is thinking");
	return (0);
}
