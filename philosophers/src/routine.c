#include "philo.h"

void	precision_sleep(t_philo *philo, long long sleep_time)
{
	long long	wake_time;

	wake_time = get_time() + sleep_time;
	while (get_time() < wake_time)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->any_philosopher_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(100);
	}
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, 0);
	precision_sleep(philo, philo->data->num_philosophers.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long long	think_time;

	write_status(philo, 1);
	pthread_mutex_lock(&philo->meal_time_lock);
	think_time = (philo->data->num_philosophers.time_to_die
			- (get_time() - philo->last_meal_time)
			- philo->data->num_philosophers.time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	else if (think_time > 50)
		think_time = 110;
	precision_sleep(philo, think_time);
}

int	philo_eat(t_philo *philo)
{
	if (one_philo(philo) == 1)
		return (1);
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
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	precision_sleep(philo, philo->data->num_philosophers.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->data->start_time)
		usleep(10);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo_eat(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->any_philosopher_died == 1)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		if (philo->data->number_of_times_each_philosopher_must_eat != -1
			&& philo->meal_eaten >= philo->data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo *philosophers)
{
	pthread_t	monitor_id;
	int			count;
	int			i;
	long long	start_time;

	count = philosophers->data->num_philosophers.num_philosophers;
	start_time = get_time() + (count * 50);
	i = 0;
	while (i < count)
	{
		philosophers[i].data->start_time = start_time;
		philosophers[i].last_meal_time = start_time;
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_create(&philosophers[i].thread_id, NULL, philosopher_routine, &philosophers[i]) != 0)
		{
			printf("Philosopher Create Thread Error\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_id, NULL, death_monitor, philosophers) != 0)
	{
		printf("Monitoring Create Thread Error\n");
		return (1);
	}
	i = 0;
	while (i < count)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
	return (0);
}
