/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 04:21:34 by agurses           #+#    #+#             */
/*   Updated: 2025/08/22 06:41:14 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_usleep(t_philo *philo, long long sleep_time)
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
	set_usleep(philo, philo->data->num_philosophers.time_to_sleep);
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
	else if (think_time > 50 && think_time < 100)
		think_time = 110;
	set_usleep(philo, think_time);
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
	set_usleep(philo, philo->data->num_philosophers.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
