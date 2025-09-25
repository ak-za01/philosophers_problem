#include "philo.h"

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->engine->time.sleep);
	}
	while (!simulation_should_end(philo->engine))
	{
		print_status(philo, "is thinking");
		if (simulation_should_end(philo->engine))
			break;
		if (eats(philo))
			break ;
		print_status(philo, "is sleeping");
		if (ft_usleep(philo->engine->time.sleep) == 1)
            break;
	}
	return (NULL);
}

void	*check_engine(void *arg)
{
	t_engine	*engine = (t_engine *)arg;
	long		current_time;
	int			a;

	while (!simulation_should_end(engine))
	{
		a = 0;
		current_time = get_time();
		while (a < engine->philo_count)
		{
			if (current_time - engine->philos[a].last_meal_time > (long)engine->time.die)
			{
				print_status(&engine->philos[a], "has died");
				pthread_mutex_lock(&engine->death_lock);
				engine->someone_died = true;
				pthread_mutex_unlock(&engine->death_lock);
				return (NULL);
			}
			a++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_engine(t_engine *engine)
{
	int	a;

	a = -1;
	while (++a < engine->philo_count)
	{
		if (pthread_create(&engine->philos[a].thread_id, NULL, 
			philosophers_routine, &engine->philos[a]))
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

int single_philosopher(t_engine *engine)
{
	printf("0 1 has taken a fork\n");
	usleep(engine->time.die * 1000);
	printf("%zu 1 died\n", engine->time.die + 1);
	return (cleanup_exit(engine, 0));
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->engine->print_lock);
	if (!simulation_should_end(philo->engine))
	{
		timestamp = get_time() - philo->engine->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->engine->print_lock);
}
