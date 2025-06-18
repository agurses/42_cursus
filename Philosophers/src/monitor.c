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
	long long current;

	pthread_mutex_lock(&philo->data->write_mutex);
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
			printf("%lld %d has taken left fork\n", current, philo->id);
		else if (status == 4)
			printf("%lld %d has taken right fork\n", current, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	int		eat_time;
	int		i;
	int		count;

	philo = (t_philo *)arg;
	count = philo->data->num_philosophers.num_philosophers;
	eat_time = philo->data->num_philosophers.time_to_die;
	while (1)
	{
		i = 0;
		while (i < count)
		{
			if ((get_time() - philo[i].last_meal_time) > eat_time)
			{
				pthread_mutex_lock(&philo->data->death_mutex);
				philo->data->any_philosopher_died = 1;
				printf("%lld %d died\n", get_time() - philo->data->start_time, philo[i].id);
				pthread_mutex_unlock(&philo->data->death_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
