/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:44:07 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 17:18:08 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	cleanup_exit(t_engine *engine, int status)
{
	cleanup_semaphores(engine);
	if (engine->philos)
		free(engine->philos);
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
	if (start_simulation(&engine))
		return (cleanup_exit(&engine, 1));
	return (cleanup_exit(&engine, 0));
}
