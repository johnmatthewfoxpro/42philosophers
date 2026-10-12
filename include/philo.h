/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:45:13 by j.fox             #+#    #+#             */
/*   Updated: 2026/10/12 12:37:44 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philos
{
	int				id;
	int				eaten;
	ssize_t			last_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_ok;
	int				meal_mut;
	t_data			*data;
	int				*dead;
}	t_philos;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_to_eat;
	int				all_eaten;
	int				dead;
	ssize_t			sim_start;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	int				fork_mut;
	pthread_mutex_t	print_ok;
	int				print_mut;
	pthread_mutex_t	dead_ok;
	int				dead_mut;
	pthread_mutex_t	finished_ok;
	int				fin_mut;
	pthread_t		monitor;
}	t_data;

int		init_data(t_data *data, int argc, char **argv);

int		ft_usleep(size_t milliseconds, t_data *data);
ssize_t	get_time(void);
void	set_time(t_data *data);

int		init_forks(t_data *data);
void	assign_forks(t_data *data);

int		create_threads(t_data *data);
void	join_thread(t_data *data);

int		simulate_finished(t_data *data);
int		simulate_death(t_data *data);
void	*monitor_routine(void *arg);

int		full(t_philos *philo);
int		pickup_fork(t_philos *philo);
int		eat(t_philos *philo);
void	drop_fork(t_philos *philo);
int		philosophize_this(t_philos *philo);

int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		is_valid_number(char *arg);
void	print_output(t_philos *philo, char *output);

void	destroy_failed_forks(t_data *data, int i);
void	clean(t_data *data);

#endif
