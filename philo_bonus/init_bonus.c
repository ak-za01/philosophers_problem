/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:00:40 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 17:19:06 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_engine_args(t_engine *engine, char **av)
{
	engine->philo_count = ft_atoi(av[1]);
	engine->time.die = ft_atoi(av[2]);
	engine->time.eat = ft_atoi(av[3]);
	engine->time.sleep = ft_atoi(av[4]);
	engine->meals_required = -1;
	if (av[5])
		engine->meals_required = ft_atoi(av[5]);
	engine->start_time = get_time();
	if (engine->start_time == -1)
		return (1);
	engine->someone_died = false;
	engine->philos_finished = 0;
	return (0);
}

void	init_philosophers(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		engine->philos[i].id = i + 1;
		engine->philos[i].pid = 0;
		engine->philos[i].meals_eaten = 0;
		engine->philos[i].last_meal_time = engine->start_time;
		engine->philos[i].engine = engine;
		i++;
	}
}

int	init_semaphores(t_engine *engine)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	engine->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644,
			engine->philo_count);
	if (engine->forks == SEM_FAILED)
		return (1);
	engine->print_sem = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (engine->print_sem == SEM_FAILED)
	{
		sem_close(engine->forks);
		sem_unlink(SEM_FORKS);
		return (1);
	}
	return (0);
}

void	cleanup_semaphores(t_engine *engine)
{
	if (engine->forks)
	{
		sem_close(engine->forks);
		sem_unlink(SEM_FORKS);
	}
	if (engine->print_sem)
	{
		sem_close(engine->print_sem);
		sem_unlink(SEM_PRINT);
	}
}

int	ft_init(t_engine *engine, char **av)
{
	if (init_engine_args(engine, av))
		return (1);
	engine->philos = malloc(engine->philo_count * sizeof(t_philo));
	if (!engine->philos)
		return (1);
	if (init_semaphores(engine))
	{
		free(engine->philos);
		return (1);
	}
	init_philosophers(engine);
	return (0);
}
