#include "philo.h"

int	init_engine_args(t_engine *engine, char **av)
{
	engine->philo_count = ft_atoi(av[1]);
	engine->time.die = ft_atoi(av[2]);
	engine->time.eat = ft_atoi(av[3]);
	engine->time.sleep = ft_atoi(av[4]);
	engine->meals_required = -1;
	if (av[5])
		engine->meals_required = ft_atoi(av[5]);
	engine->start_time = get_time();
	if (engine->start_time == -1)
		return (1);
	engine->someone_died = false;
	engine->philos_finished = 0;
	return (0);
}

void init_philosophers(t_engine *engine)
{
	int	a;

	a = 0;
	while (a < engine->philo_count)
	{
		engine->philos[a].id = a + 1;
		engine->philos[a].left_fork = &engine->forks[a];
		engine->philos[a].right_fork = NULL;
		if (engine->philo_count > 1)
			engine->philos[a].right_fork = &engine->forks[(a + 1) % engine->philo_count];
		engine->philos[a].meals_eaten = 0;
		engine->philos[a].last_meal_time = get_time();
		engine->philos[a].engine = engine;
		a++;
	}
}

int	mutex_init(t_engine *engine)
{
	int	a;

	a = -1;
	while (++a < engine->philo_count)
	{
		if (pthread_mutex_init(&engine->forks[a], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&engine->meal_lock, NULL) != 0)
			return (1);
	if (pthread_mutex_init(&engine->death_lock, NULL) != 0)
			return (1);
	if (pthread_mutex_init(&engine->print_lock, NULL) != 0)
			return (1);
	return (0);
}

int	ft_init(t_engine *engine, char **av)
{
	if (init_engine_args(engine, av))
		return (1);
	engine->forks = malloc(engine->philo_count * sizeof(pthread_mutex_t));
	if (!engine->forks)
		return (1);
	engine->philos = malloc(engine->philo_count * sizeof(t_philo));
	if (!engine->philos)
	{
		free(engine->forks);
		return (1);
	}
	if (mutex_init(engine))
	{
		free(engine->forks);
		free(engine->philos);
		return (1);
	}
	init_philosophers(engine);
	return (0);
}
