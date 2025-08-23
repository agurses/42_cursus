/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 04:21:10 by agurses           #+#    #+#             */
/*   Updated: 2025/08/22 04:28:04 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (philo->data->any_philosopher_died == 1
			|| (philo->data->number_of_times_each_philosopher_must_eat != -1
				&& philo->meal_eaten
				>= philo->data->number_of_times_each_philosopher_must_eat))
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

void	init_simulation_time(t_philo *philosophers, long long start_time)
{
	int	count;
	int	i;

	count = philosophers->data->num_philosophers.num_philosophers;
	i = 0;
	while (i < count)
	{
		philosophers[i].data->start_time = start_time;
		philosophers[i].last_meal_time = start_time;
		i++;
	}
}

int	create_philosopher_threads(t_philo *philosophers)
{
	int	count;
	int	i;

	count = philosophers->data->num_philosophers.num_philosophers;
	i = 0;
	while (i < count)
	{
		if (pthread_create(&philosophers[i].thread_id, NULL,
				philosopher_routine, &philosophers[i]) != 0)
		{
			printf("Philosopher Create Thread Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_all_threads(t_philo *philosophers, pthread_t monitor_id)
{
	int	count;
	int	i;

	count = philosophers->data->num_philosophers.num_philosophers;
	i = 0;
	while (i < count)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
	return (0);
}

int	start_simulation(t_philo *philosophers)
{
	pthread_t	monitor_id;
	int			count;
	long long	start_time;

	count = philosophers->data->num_philosophers.num_philosophers;
	start_time = get_time() + (count * 50);
	init_simulation_time(philosophers, start_time);
	if (create_philosopher_threads(philosophers) != 0)
		return (1);
	if (pthread_create(&monitor_id, NULL, death_monitor, philosophers) != 0)
	{
		printf("Monitoring Create Thread Error\n");
		return (1);
	}
	join_all_threads(philosophers, monitor_id);
	return (0);
}
