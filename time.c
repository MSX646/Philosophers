/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:06:55 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:37:50 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	wait_to_time(t_philo *phl, int sleep_to_time_ms)
{
	unsigned long	start;
	unsigned long	now;

	start = phl->data->time_start;
	now = get_time_ms();
	while (now < start + sleep_to_time_ms)
	{
		usleep(SLEEP / 10);
		now = get_time_ms();
	}
	return (0);
}

int	wait_start(t_philo *phl)
{
	int	first;
	int	second;
	int	third;

	first = START_MS;
	second = START_MS + phl->data->t_eat;
	third = START_MS * 2 + phl->data->t_eat;
	if (phl->data->num_phil == 1)
		wait_to_time(phl, first);
	else if (phl->id % 2 == 0)
		wait_to_time(phl, second);
	else
	{
		if (phl->data->num_phil % 2 == 0)
			wait_to_time(phl, first);
		else
		{
			if (phl->id == phl->data->num_phil)
				wait_to_time(phl, third);
			else
				wait_to_time(phl, first);
		}
	}
	return (0);
}

void	ft_usleep(int sleep_time_ms)
{
	unsigned long	start;
	unsigned long	now;

	start = get_time_ms();
	now = start;
	while (now < start + sleep_time_ms)
	{
		usleep(SLEEP);
		now = get_time_ms();
	}
}
