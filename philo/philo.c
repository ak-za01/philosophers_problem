/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:44:07 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/02 15:09:54 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_engine *engine)
{
	int	a;

	a = 0;
	if (engine->forks)
	{
		while (a < engine->philo_count)
		{
			pthread_mutex_destroy(&engine->forks[a]);
			pthread_mutex_destroy(&engine->philos[a].meal_time_lock);
			a++;
		}
	}
	pthread_mutex_destroy(&engine->meal_lock);
	pthread_mutex_destroy(&engine->death_lock);
	pthread_mutex_destroy(&engine->print_lock);
}

int	cleanup_exit(t_engine *engine, int status)
{
	destroy_mutexes(engine);
	if (engine->philos)
		free(engine->philos);
	if (engine->forks)
		free(engine->forks);
	return (status);
}

int	main(int ac, char **av)
{
	t_engine	engine;

	if (check_args(ac, av) != 0)
		return (1);
	memset(&engine, 0, sizeof(t_engine));
	if (ft_init(&engine, av) != 0)
		return (cleanup_exit(&engine, 1));
	if (start_engine(&engine))
		return (cleanup_exit(&engine, 1));
	return (cleanup_exit(&engine, 0));
}
