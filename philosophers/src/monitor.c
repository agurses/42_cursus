#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->num_philosophers.num_philosophers == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, 4);
		usleep(philo->data->num_philosophers.time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

void	write_status(t_philo *philo, int status)
{
	long long	current;

	pthread_mutex_lock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	current = get_time() - philo->data->start_time;
	if (!philo->data->any_philosopher_died)
	{
		if (status == 0)
			printf("%lld %d is sleeping\n", current, philo->id);
		else if (status == 1)
			printf("%lld %d is thinking\n", current, philo->id);
		else if (status == 2)
			printf("%lld %d is eating\n", current, philo->id);
		else if (status == 3)
			printf("%lld %d has taken fork\n", current, philo->id);
		else if (status == 4)
			printf("%lld %d has taken fork\n", current, philo->id);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	int		time_to_die;
	int		i;
	int		count;
	int		finished_eating;

	philo = (t_philo *)arg;
	count = philo->data->num_philosophers.num_philosophers;
	time_to_die = philo->data->num_philosophers.time_to_die;
	while (1)
	{
		i = -1;
		finished_eating = 0;
		while (++i < count)
		{
			pthread_mutex_lock(&philo[i].meal_time_lock);
			if ((get_time() - philo[i].last_meal_time) >= time_to_die)
			{
				pthread_mutex_lock(&philo->data->write_mutex);
				pthread_mutex_lock(&philo->data->death_mutex);
				philo->data->any_philosopher_died = 1;
				printf("%lld %d died\n", get_time() - philo->data->start_time, philo[i].id);
				pthread_mutex_unlock(&philo->data->death_mutex);
				pthread_mutex_unlock(&philo->data->write_mutex);
				pthread_mutex_unlock(&philo[i].meal_time_lock);
				return (NULL);
			}
			if (philo->data->number_of_times_each_philosopher_must_eat != -1 
				&& philo[i].meal_eaten >= philo->data->number_of_times_each_philosopher_must_eat)
				finished_eating++;
			pthread_mutex_unlock(&philo[i].meal_time_lock);
		}
		if (philo->data->number_of_times_each_philosopher_must_eat != -1 
			&& finished_eating >= count)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->any_philosopher_died = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
