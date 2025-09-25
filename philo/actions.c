#include "philo.h"

bool	simulation_should_end(t_engine *engine)
{
	bool	dead;
	int		finished;

	pthread_mutex_lock(&engine->death_lock);
	dead = engine->someone_died;
	pthread_mutex_unlock(&engine->death_lock);
	if (dead)
		return (true);
	if (engine->meals_required > 0)
	{
		pthread_mutex_lock(&engine->meal_lock);
		finished = engine->philos_finished;
		pthread_mutex_unlock(&engine->meal_lock);
		if (finished >= engine->philo_count)
			return (true);
	}
	return (false);
}

int	ft_usleep(long milliseconds)
{
	long	start_time;
	long	current_time;

	start_time = get_time();
	while ((current_time = get_time()) - start_time < milliseconds)
	{
		usleep(500);
	}
	return (0);
}

int	eats(t_philo *philo)
{
	int	meals_required;

	meals_required = philo->engine->meals_required;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->engine->time.eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (meals_required > 0 && philo->meals_eaten >= meals_required)
	{
		pthread_mutex_lock(&philo->engine->meal_lock);
		philo->engine->philos_finished++;
		pthread_mutex_unlock(&philo->engine->meal_lock);
	}
	return (0);
}
