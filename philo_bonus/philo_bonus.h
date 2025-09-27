/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:41:05 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 XX:XX:XX by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
#include <pthread.h>
# include <signal.h>
# include <fcntl.h>

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
	pid_t				pid;
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
	sem_t				*forks;
	sem_t				*print_sem;
	sem_t				*death_sem;
	sem_t				*meal_count_sem;
	long				start_time;
	bool				someone_died;
	int					philos_finished;
}	t_engine;


int		check_args(int ac, char **av);
int		ft_init(t_engine *engine, char **av);
int		ft_atoi(char *str);
long	get_time(void);
int		cleanup_exit(t_engine *engine, int status);
int		start_simulation(t_engine *engine);
void	philosopher_process(t_philo *philo);
void	print_status(t_philo *philo, char *status);
int		ft_usleep(long milliseconds);
int		philo_eats(t_philo *philo);
void	philo_sleeps(t_philo *philo);
void	philo_thinks(t_philo *philo);
void	*death_monitor(void *arg);
void	cleanup_semaphores(t_engine *engine);
int		init_semaphores(t_engine *engine);

/* Semaphore names */
# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print" 
# define SEM_DEATH "/philo_death"
# define SEM_MEALS "/philo_meals"

#endif