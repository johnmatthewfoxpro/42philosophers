/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:11:22 by jfox              #+#    #+#             */
/*   Updated: 2026/10/15 11:55:30 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

int	ft_usleep(ssize_t milliseconds, t_data *data)
{
	ssize_t	start;

	(void)data;
	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if (simulate_death(data))
			return (1);
		usleep(500);
	}
	return (0);
}
