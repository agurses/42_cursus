/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 04:21:20 by agurses           #+#    #+#             */
/*   Updated: 2025/08/22 04:29:37 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

# define MAX_PHILO 200

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_time_lock;
	pthread_t		thread_id;
	int				id;
	int				meal_eaten;
	long long		last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_num_philo
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_num_philo;

typedef struct s_data
{
	t_num_philo		num_philosophers;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	int				any_philosopher_died;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
}	t_data;

long		ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			init_philosophers(char **argv, t_philo **philosophers);
int			start_simulation(t_philo *philosophers);
void		*death_monitor(void *arg);
void		write_status(t_philo *philo, int status);
int			one_philo(t_philo *philo);
long long	get_time(void);
int			check_philosopher_death(t_philo *philo, int i, int time_to_die);
int			check_meals_finished(t_philo *philo, int count);
void		init_simulation_time(t_philo *philosophers, long long start_time);
int			create_philosopher_threads(t_philo *philosophers);
int			join_all_threads(t_philo *philosophers, pthread_t monitor_id);
void		*philosopher_routine(void *arg);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
int			philo_eat(t_philo *philo);
#endif