/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:41:05 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/25 17:02:49 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
#include <semaphore.h>

typedef struct s_engine	t_engine;

typedef struct s_time
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
}	t_time;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_time_lock;
	int					meals_eaten;
	long				last_meal_time;
	t_engine			*engine;
}	t_philo;

typedef struct s_engine
{
	int					philo_count;
	t_time				time;
	int					meals_required;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		print_lock;
	pthread_t			monitor;
	int					philos_finished;
	long				start_time;
	bool				someone_died;
}	t_engine;

int		check_args(int ac, char **av);
int		ft_init(t_engine *engine, char **av);
int		ft_atoi(char *str);
long	get_time(void);
int		cleanup_exit(t_engine *engine, int status);
int		start_engine(t_engine *engine);
void	*philosophers_routine(void *arg);
void	*check_engine(void *arg);
void	print_status(t_philo *philo, char *status);
bool	simulation_should_end(t_engine *engine);
int		ft_usleep(long milliseconds, t_engine *engine);
int		eats(t_philo *philo);

#endif