/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:23:23 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 17:32:56 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all_processes(t_engine *engine, pid_t exclude_pid)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		if (engine->philos[i].pid > 0 && engine->philos[i].pid != exclude_pid)
			kill(engine->philos[i].pid, SIGTERM);
		i++;
	}
}

int	handle_process_exit(t_engine *engine, pid_t wpid, int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (1);
		else if (WEXITSTATUS(status) == 1)
		{
			kill_all_processes(engine, wpid);
			while (waitpid(-1, &status, 0) > 0)
				continue ;
			return (-1);
		}
	}
	return (0);
}

void	philosopher_process(t_philo *philo)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, death_monitor, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->engine->time.sleep);
	}
	while (1)
	{
		print_status(philo, "is thinking");
		philo_eats(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->engine->time.sleep);
	}
	exit(0);
}
