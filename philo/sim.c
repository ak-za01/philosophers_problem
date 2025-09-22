#include "philo.h"

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (check_engine_light(philo))
	{
		thinks(philo);
		if (eats(philo))
			break ;
		sleeps(philo);
	}
	return (NULL);
}

void	check_engine(void *arg)
{

	return (NULL);
}

int	start_engine(t_engine *engine)
{
	int	a;

	a = -1;
	while (++a < engine->philo_count)
	{
		if (pthread_create(&engine->philos[a].thread_id, NULL, routine, &engine->philos[a]))
		{
			printf("Error: Failed to create philosopher thread %d\n", a + 1);
			return (1);
		}
	}
	if (pthread_create(&engine->monitor, NULL, check_engine, engine))
	{
		printf("Error: Failed to create monitor thread \n");
			return (1);
	}
	pthread_join(engine->monitor, NULL);
	a = -1;
	while (++a < engine->philo_count)
		pthread_join(engine->philos[a].thread_id, NULL);
	return (0);
}
