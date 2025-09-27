/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:52:33 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/27 XX:XX:XX by anktiri          ###   ########.fr       */
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