/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:02:15 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:32:38 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_time(t_philo	*phl)
{
	pthread_mutex_lock(&phl->data->last_eat_m);
	if (get_time_ms() - phl->last_eat <= phl->data->t_die)
	{
		pthread_mutex_unlock(&phl->data->last_eat_m);
		return (1);
	}
	pthread_mutex_unlock(&phl->data->last_eat_m);
	return (0);
}

int	check_eat(t_philo	*phl)
{
	pthread_mutex_lock(&phl->data->num_eat_m);
	if (phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		return (0);
	}
}

int	check_data_dead(t_philo *phl, int mode)
{
	pthread_mutex_lock(&phl->data->data_dead_m);
	pthread_mutex_lock(&phl->data->num_eat_m);
	if ((mode == 1 && \
	(phl->data->death != 1 && phl->num_eat <= phl->data->max_eat)) || \
	(mode == 2 && !check_error(phl->data) && \
	(phl->data->max_eat != -1 && phl->num_eat >= phl->data->max_eat)) || \
	(mode == 3 && \
	(phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)))
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		pthread_mutex_unlock(&phl->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&phl->data->num_eat_m);
	pthread_mutex_unlock(&phl->data->data_dead_m);
	return (0);
}
