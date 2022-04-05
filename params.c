/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:02:37 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:38:29 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		n;
	int		flag;
	size_t	len_num;

	n = 0;
	flag = 1;
	len_num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			flag *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str++ - '0');
		if (len_num++ > 12 && flag == 1)
			return (-1);
		else if (len_num > 12 && flag == -1)
			return (0);
	}
	return (n * flag);
}

static void	def_params(t_data *data)
{
	data->error = 0;
	data->max_eat = -1;
	data->death = 0;
	data->time_start = 0;
	return ;
}

static int	get_param(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		set_error(data, 2, \
			"USAGE: n_of_philo die_time eat_time sleep_time <n_of_meals>\n");
	else
	{
		data->num_phil = ft_atoi(argv[1]);
		data->t_die = ft_atoi(argv[2]);
		data->t_eat = ft_atoi(argv[3]);
		data->t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->max_eat = ft_atoi(argv[5]);
	}
	if (data->error)
		return (0);
	if (data->num_phil < 0 || data->t_die < 1 || data->t_sleep < 1 || \
	data->t_eat < 1 || data->t_sleep < 1 || (argc == 6 && data->max_eat < 0))
		return (set_error(data, 2, "Incorrect values\n"));
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (pthread_mutex_init(&data->error_m, NULL))
		return (set_error(data, 1, "Mutex error\n"));
	def_params(data);
	get_param(data, argc, argv);
	return (0);
}
