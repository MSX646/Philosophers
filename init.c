/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:02:29 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:39:12 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutexs_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->last_eat_m, NULL))
		return (set_error(data, 3, "Error init  mutex\n"));
	if (pthread_mutex_init(&data->data_dead_m, NULL))
		return (set_error(data, 4, "Error init  mutex\n"));
	if (pthread_mutex_init(&data->num_eat_m, NULL))
		return (set_error(data, 5, "Error init  mutex\n"));
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[--i]);
			return (set_error(data, 6, "Error init  mutex\n"));
		}
	}
	return (0);
}

int	init_forks_time(t_data *data)
{
	struct timeval	time;

	if (check_error(data))
		return (0);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num_phil);
	if (!data->forks)
		return (set_error(data, 2, "Malloc data.forks\n"));
	if (gettimeofday(&time, NULL))
		return (set_error(data, 3, "Malloc data.forks\n"));
	data->time_start = (time.tv_sec * 1000 + time.tv_usec / 1000);
	mutexs_init(data);
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	if (check_error(data))
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_join(data->philo_t[i], NULL);
		i++;
	}
}

static t_philo	*init_philo_struct(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_phil);
	if (!philo)
		set_error(data, 7, "Error malloc philo\n");
	if (check_error(data))
		return (NULL);
	i = 0;
	while (++i <= data->num_phil)
	{
		philo[i - 1].id = i;
		philo[i - 1].data = data;
		philo[i - 1].last_eat = 0;
		if (data->max_eat != -1)
			philo[i - 1].num_eat = 0;
		else
			philo[i - 1].num_eat = -1;
		philo[i - 1].l_fork = i;
		philo[i - 1].r_fork = get_r_fork(i, data);
		philo[i - 1].max_fork = max_fork(&philo[i - 1]);
		philo[i - 1].min_fork = min_fork(&philo[i - 1]);
		philo[i - 1].last_eat = data->time_start + START_MS;
	}
	return (philo);
}

int	init_philo(t_data *data, t_philo **arg)
{
	int		i;

	if (check_error(data))
		return (0);
	*arg = init_philo_struct(data);
	if (check_error(data))
		return (0);
	data->philo_t = (pthread_t *)malloc(sizeof(pthread_t) * data->num_phil);
	if (!data->philo_t)
		return (set_error(data, 8, "Error malloc for data.philo\n"));
	i = -1;
	while (++i < data->num_phil)
	{
		if (pthread_create(&data->philo_t[i], NULL, live_cycle, &(*arg)[i]))
		{
			set_error(data, 9, "Error pthread create\n");
			while (--i >= 0)
				pthread_join(data->philo_t[i], NULL);
			return (0);
		}
	}
	return (0);
}
