/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:12:26 by jfox              #+#    #+#             */
/*   Updated: 2026/10/14 18:47:13 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	if (ft_atoi(arg) == 0)
		return (1);
	return (0);
}

void	print_output(t_philos *philo, char *output)
{
	ssize_t	time;

	pthread_mutex_lock(&philo->data->print_ok);
	time = get_time() - philo->data->sim_start;
	if (simulate_death(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_ok);
		return ;
	}
	printf("%zd %d %s\n", time, philo->id, output);
	pthread_mutex_unlock(&philo->data->print_ok);
	return ;
}
