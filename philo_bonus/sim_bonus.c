/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:20:20 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/25 17:09:52 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->engine->time.sleep, philo->engine);
	}
	while (!simulation_should_end(philo->engine))
	{
		print_status(philo, "is thinking");
		if (simulation_should_end(philo->engine))
			break ;
		if (eats(philo))
			break ;
		print_status(philo, "is sleeping");
		if (ft_usleep(philo->engine->time.sleep, philo->engine) == 1)
			break ;
	}
	return (NULL);
}

void	*check_engine(void *arg)
{
	t_engine	*engine;
	long		current_time;
	int			a;

	engine = (t_engine *)arg;
	while (!simulation_should_end(engine))
	{
		current_time = ((a = -1), get_time());
		while (++a < engine->philo_count)
		{
			pthread_mutex_lock(&engine->philos[a].meal_time_lock);
			if (current_time - engine->philos[a].last_meal_time 
				> (long)engine->time.die)
			{
				print_status(&engine->philos[a], "died");
				pthread_mutex_lock(&engine->death_lock);
				engine->someone_died = true;
				pthread_mutex_unlock(&engine->philos[a].meal_time_lock);
				return (pthread_mutex_unlock(&engine->death_lock), NULL);
			}
			pthread_mutex_unlock(&engine->philos[a].meal_time_lock);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_engine(t_engine *engine)
{
	int	a;

	a = -1;
	while (++a < engine->philo_count)
	{
		if (pthread_create(&engine->philos[a].thread_id, NULL, 
				philosophers_routine, &engine->philos[a]))
		{
			printf("Error: Failed to create philosopher thread %d\n", a + 1);
			return (1);
		}
	}
	if (pthread_create(&engine->monitor, NULL, check_engine, engine))
	{
		printf("Error: Failed to create monitor thread \n");
		return (1);
	}
	pthread_join(engine->monitor, NULL);
	a = -1;
	while (++a < engine->philo_count)
		pthread_join(engine->philos[a].thread_id, NULL);
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->engine->print_lock);
	if (!simulation_should_end(philo->engine))
	{
		timestamp = get_time() - philo->engine->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->engine->print_lock);
}
