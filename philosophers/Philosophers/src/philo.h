#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>

# define MAX_PHILO 200

typedef struct s_data t_data;

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
	pthread_mutex_t write_mutex;
	pthread_mutex_t death_mutex;
	pthread_mutex_t *forks;
	int				any_philosopher_died;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	//sem_t			waiter;
}	t_data;

//utils.c
long	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

//init.c
int		init_philosophers(char ** argv, t_philo **philosophers);

//routine.c
int start_simulation(t_philo *philosophers);


//monitor.c
void	*death_monitor(void *arg);
void	write_status(t_philo *philo, int status);
int		one_philo(t_philo *philo);

//time.c
long long	get_time(void);

#endif