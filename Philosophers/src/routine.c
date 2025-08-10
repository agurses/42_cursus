#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	write_status(philo, 0);
	usleep(philo->data->num_philosophers.time_to_sleep * 1000);
}
void	philo_think(t_philo *philo)
{
	write_status(philo, 1);
}
void	philo_eat(t_philo *philo)
{
	if (one_philo(philo) == 1)
		return;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, 3);
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, 4);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, 4);
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, 3);
	}
	write_status(philo, 2);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->num_philosophers.time_to_eat * 1000);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		//pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->any_philosopher_died == 1)
		{
			//pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		//pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->data->number_of_times_each_philosopher_must_eat != -1 
			&& philo->meal_eaten >= philo->data->number_of_times_each_philosopher_must_eat)
			break;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int start_simulation(t_philo *philosophers)
{
	pthread_t	monitor_id;
	int			count;
	int			i;

	i = -1;
	count = philosophers->data->num_philosophers.num_philosophers;
	while (++i < count)
	{
		philosophers[i].last_meal_time = get_time();
		if (pthread_create(&philosophers[i].thread_id, NULL, philosopher_routine, &philosophers[i]) != 0) ////// buna çalış
		{
			printf("Philosopher Create Thread Error\n");
			return (1);
		}
	}
	if (pthread_create(&monitor_id, NULL,death_monitor, philosophers) != 0)
	{
		printf("Monitoring Create Thread Error\n");
		return (1);
	}
	pthread_detach(monitor_id);
	i = -1;
	while (++i < count)
		pthread_join(philosophers[i].thread_id, NULL);
	return (0);
}
