/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:52:33 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/25 16:52:49 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	simulation_should_end(t_engine *engine)
{
	bool	dead;
	int		finished;

	pthread_mutex_lock(&engine->death_lock);
	dead = engine->someone_died;
	pthread_mutex_unlock(&engine->death_lock);
	if (dead)
		return (true);
	if (engine->meals_required > 0)
	{
		pthread_mutex_lock(&engine->meal_lock);
		finished = engine->philos_finished;
		pthread_mutex_unlock(&engine->meal_lock);
		if (finished >= engine->philo_count)
			return (true);
	}
	return (false);
}

int	ft_usleep(long milliseconds, t_engine *engine)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < milliseconds)
	{
		if (simulation_should_end(engine))
			return (1);
		usleep(500);
	}
	return (0);
}

int	eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (!philo->right_fork)
	{
		ft_usleep(philo->engine->time.die + 1, philo->engine);
		return (pthread_mutex_unlock(philo->left_fork), 1);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_usleep(philo->engine->time.eat, philo->engine);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->engine->meals_required > 0 && 
		philo->meals_eaten >= philo->engine->meals_required)
	{
		pthread_mutex_lock(&philo->engine->meal_lock);
		philo->engine->philos_finished++;
		pthread_mutex_unlock(&philo->engine->meal_lock);
	}
	return (0);
}
