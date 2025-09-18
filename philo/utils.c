/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:52:51 by anktiri           #+#    #+#             */
/*   Updated: 2025/09/17 19:22:46 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_2(int a)
{
	if (a)
	{
		printf("╚═══════ WARNING: INCORRECT ARGS MAY RESULT IN PHILOSOPHICAL CHAOS ═══════╝\n");
		return ;
	}
	printf("╠════════════════ PHILOSOPHER SURVIVAL GUIDE ═════════════════════════════╣\n");
	printf("║                                                                         ║\n");
	printf("║  Remember: Philosophers need time to eat, think, and sleep!             ║\n");
	printf("║                                                                         ║\n");
	printf("║  • time_to_die      : How long before starvation (milliseconds)         ║\n");
	printf("║  • time_to_eat      : Duration of eating session (milliseconds)         ║\n");
	printf("║  • time_to_sleep    : How long philosophers rest (milliseconds)         ║\n");
	printf("║  • meals_count    : Optional - stop after N meals per philosopher       ║\n");
	printf("║                                                                         ║\n");
	printf("║  Example: ./philo 5 800 200 200 7                                       ║\n");
	printf("║       5 philosophers, die in 800ms, eat 200ms, sleep 200ms, 7 meals     ║\n");
	printf("║                                                                         ║\n");
	printf("╚═══════ WARNING: INCORRECT ARGS MAY RESULT IN PHILOSOPHICAL CHAOS ═══════╝\n");
	printf("\033[0m\n");
}

void	message(int a)
{
	printf("\033[1;37m\n");
	printf("╔══════════════ PHILOSOPHERS: DINING & DYING SIMULATOR ═══════════════════╗\n");
	printf("║                                                                         ║\n");
	printf("║  Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat]    ║\n");
	printf("║                 [time_to_sleep] [number_of_times_each_must_eat]         ║\n");
	printf("║                                                                         ║\n");
	printf("║  Arguments (all required except last):                                  ║\n");
	printf("║    - number_of_philosophers : How many thinkers join the table (1-200)  ║\n");
	printf("║    - time_to_die           : Death timer in milliseconds (> 0)          ║\n");
	printf("║    - time_to_eat           : Eating duration in milliseconds (> 0)      ║\n");
	printf("║    - time_to_sleep         : Sleeping duration in milliseconds (> 0)    ║\n");
	printf("║    - meals_count           : [OPTIONAL] Stop after N meals per philo    ║\n");
	printf("║                                                                         ║\n");
	printf("║  Note: All times are in milliseconds, all values must be positive       ║\n");
	printf("║                                                                         ║\n");
	message_2(a);
}

int	ft_atoi(char *str)
{
	long 	res;
	int		sign;
	int		a;

	res = 0;
	sign =  1;
	a = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign = -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		res = res * 10 + (str[a] - '0');
		a++;
		if (res > INT_MAX)
			return (0);
	}
	return (res * sign);
}

int	check_args(int ac, char **av)
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_count;

	if (ac < 5 || ac > 6)
		return (message(1), 1);
	nb_philo = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	meals_count = -1;
	if (ac == 6)
		meals_count = ft_atoi(av[5]);
	if (nb_philo <= 0 || nb_philo > 200 || time_to_die <= 0 || 
		time_to_eat <= 0 || time_to_sleep <= 0 || (ac == 6 && meals_count < 0))
		return (message(0), 1);
	return (0);
}

long	get_time(void)
{
	struct	timeval	timeval;

	if (gettimeofday(&timeval, NULL) == -1)
		return (-1);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}
