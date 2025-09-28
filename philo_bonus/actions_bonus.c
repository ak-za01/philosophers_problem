/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:52:33 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/28 13:44:46 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(long milliseconds)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < milliseconds)
	{
		usleep(500);
	}
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->engine->print_sem);
	timestamp = get_time() - philo->engine->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	if (strcmp(status, "died") != 0)
		sem_post(philo->engine->print_sem);
}

int	philo_eats(t_philo *philo)
{
	sem_wait(philo->engine->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->engine->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->engine->time.eat);
	sem_post(philo->engine->forks);
	sem_post(philo->engine->forks);
	if (philo->engine->meals_required > 0
		&& philo->meals_eaten >= philo->engine->meals_required)
		exit(0);
	return (0);
}
