/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:44:07 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/13 19:01:21 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_engine	engine;
	if (check_args(ac, av) != 0)
		return (1);
	memset(&engine, 0, sizeof(t_engine));
	if (ft_init(&engine, av) != 0)
		return (1);
	return (0);
}
