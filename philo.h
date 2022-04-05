/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:02:02 by kezekiel          #+#    #+#             */
/*   Updated: 2022/03/23 14:43:38 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define TAKE_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DIED "died\n"
# define START_MS 60
# define SLEEP 500

typedef struct s_data
{
	int				num_phil;
	unsigned long	t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	pthread_t		*philo_t;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_eat_m;
	pthread_mutex_t	data_dead_m;
	pthread_mutex_t	num_eat_m;
	pthread_mutex_t	error_m;
	int				death;
	int				error;
	unsigned long	time_start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	unsigned long	last_eat;
	int				num_eat;
	int				l_fork;
	int				r_fork;
	int				max_fork;
	int				min_fork;
}	t_philo;

//philo.c
void			ft_philo(int argc, char **argv);
void			*live_cycle(void *arg);
//params.c
int				init_data(t_data *data, int argc, char **argv);
//error.c
int				set_error(t_data *data, int error, char *message);
int				check_error(t_data *data);
void			clean_exit(t_data *data, t_philo *philo);
int				exit_philo(t_data *data, t_philo *philo);
//init.c
int				init_philo(t_data *data, t_philo **arg);
int				init_forks_time(t_data *data);
void			join_threads(t_data *data);
//time.c
void			ft_usleep(int sleep_time_ms);
int				wait_start(t_philo *phl);
unsigned long	get_time_ms(void);
//action.c
int				take_forks(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
//utilit.c
int				min_fork(t_philo *philo);
int				max_fork(t_philo *philo);
int				get_r_fork(int i, t_data *data);
int				status(t_philo *philo, char *str);
//condition.c
int				check_time(t_philo	*phl);
int				check_eat(t_philo	*phl);
int				check_data_dead(t_philo *phl, int mode);

#endif
