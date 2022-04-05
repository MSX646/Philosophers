/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:57:12 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:36:06 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*phl;

	phl = (t_philo *)arg;
	while (check_time(phl))
	{
		if (check_eat(phl))
			return (NULL);
		ft_usleep(1);
	}
	pthread_mutex_lock(&phl->data->data_dead_m);
	if (phl->data->death != 1)
	{
		phl->data->death = 1;
		printf("[%lums] %d %s", \
			get_time_ms() - phl->data->time_start - START_MS, phl->id, DIED);
	}
	pthread_mutex_unlock(&phl->data->data_dead_m);
	return (NULL);
}

void	*live_cycle(void *arg)
{
	t_philo			*phl;
	pthread_t		death_t;

	phl = (t_philo *)arg;
	if (check_error(phl->data))
		return (NULL);
	wait_start(phl);
	pthread_create(&death_t, NULL, check_time_death, phl);
	while (check_data_dead(phl, 1))
	{
		if (check_data_dead(phl, 2))
			break ;
		if (take_forks(phl) == 0)
			break ;
		if (eating(phl) == 0)
			break ;
		if (sleeping(phl) == 0)
			break ;
		if (check_data_dead(phl, 3))
			break ;
		if (thinking(phl) == 0)
			break ;
	}
	pthread_join(death_t, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	init_data(&data, argc, argv);
	init_forks_time(&data);
	init_philo(&data, &philo);
	join_threads(&data);
	clean_exit(&data, philo);
	return (0);
}
