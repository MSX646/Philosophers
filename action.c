/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:02:09 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:34:33 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->forks[philo->min_fork]);
	if (status(philo, TAKE_FORK) == 0 || philo->data->num_phil == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->max_fork]);
	if (status(philo, TAKE_FORK) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (status(philo, EATING) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->last_eat_m);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->last_eat_m);
	pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
	pthread_mutex_lock(&philo->data->num_eat_m);
	if (philo->num_eat != -1)
		philo->num_eat++;
	pthread_mutex_unlock(&philo->data->num_eat_m);
	return (1);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (status(philo, SLEEPING) == 0)
		return (0);
	ft_usleep(philo->data->t_sleep);
	return (1);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (status(philo, THINKING) == 0)
		return (0);
	if (philo->data->t_eat > philo->data->t_sleep)
		ft_usleep(philo->data->t_eat - philo->data->t_sleep);
	ft_usleep(1);
	return (1);
}
