/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:20:20 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/28 12:27:14 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_processes(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		engine->philos[i].pid = fork();
		if (engine->philos[i].pid == 0)
			philosopher_process(&engine->philos[i]);
		else if (engine->philos[i].pid < 0)
		{
			printf("Error: Failed to create philosopher process %d\n",
				i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_engine *engine)
{
	int		status;
	int		finished_count;
	int		result;
	pid_t	wpid;

	if (create_processes(engine))
		return (1);
	finished_count = 0;
	while (finished_count < engine->philo_count)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid > 0)
		{
			result = handle_process_exit(engine, wpid, status);
			if (result == 1)
				finished_count++;
			else if (result == -1)
				break ;
		}
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		current_time = get_time();
		if (current_time - philo->last_meal_time
			> (long)philo->engine->time.die)
		{
			print_status(philo, "died");
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
