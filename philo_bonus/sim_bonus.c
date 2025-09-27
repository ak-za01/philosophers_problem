/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:20:20 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 XX:XX:XX by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	// Take two forks from the semaphore
	sem_wait(philo->engine->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->engine->forks);
	print_status(philo, "has taken a fork");
	
	// Eat
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->engine->time.eat);
	
	// Put forks back
	sem_post(philo->engine->forks);
	sem_post(philo->engine->forks);
	
	// Check if finished eating required meals
	if (philo->engine->meals_required > 0 && 
		philo->meals_eaten >= philo->engine->meals_required)
	{
		sem_wait(philo->engine->meal_count_sem);
		philo->engine->philos_finished++;
		if (philo->engine->philos_finished >= philo->engine->philo_count)
		{
			sem_post(philo->engine->death_sem); // Signal simulation end
		}
		sem_post(philo->engine->meal_count_sem);
		return (1);
	}
	return (0);
}

void	philo_sleeps(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->engine->time.sleep);
}

void	philo_thinks(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		current_time = get_time();
		if (current_time - philo->last_meal_time > (long)philo->engine->time.die)
		{
			print_status(philo, "died");
			sem_post(philo->engine->death_sem);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	philosopher_process(t_philo *philo)
{
	pthread_t	monitor_thread;

	// Create death monitor thread for this philosopher
	if (pthread_create(&monitor_thread, NULL, death_monitor, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);

	// Stagger start for even philosophers
	if (philo->id % 2 == 0)
	{
		philo_sleeps(philo);
	}

	while (1)
	{
		philo_thinks(philo);
		if (philo_eats(philo))
			break;
		philo_sleeps(philo);
	}
	exit(0);
}

int	start_simulation(t_engine *engine)
{
	int		i;
	int		status;
	pid_t	wpid;

	// Create philosopher processes
	i = 0;
	while (i < engine->philo_count)
	{
		engine->philos[i].pid = fork();
		if (engine->philos[i].pid == 0)
		{
			// Child process - become philosopher
			philosopher_process(&engine->philos[i]);
		}
		else if (engine->philos[i].pid < 0)
		{
			printf("Error: Failed to create philosopher process %d\n", i + 1);
			return (1);
		}
		i++;
	}

	// Main process waits for death signal or completion
	sem_wait(engine->death_sem);

	// Kill all philosopher processes
	i = 0;
	while (i < engine->philo_count)
	{
		kill(engine->philos[i].pid, SIGTERM);
		i++;
	}

	// Wait for all processes to terminate
	while ((wpid = waitpid(-1, &status, WNOHANG)) > 0)
		continue;

	return (0);
}
