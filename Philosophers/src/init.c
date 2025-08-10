#include "philo.h"

void	fill_philosophers(t_philo ** philosophers, int philo_count)
{
	int i;

	i = 0;
	while (i < philo_count)
    {
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].meal_eaten = 0;
		(*philosophers)[i].last_meal_time = 0;
		(*philosophers)[i].data = (*philosophers)[0].data;
		(*philosophers)[i].left_fork = &((*philosophers)->data->forks[i]);
		(*philosophers)[i].right_fork = &((*philosophers)->data->forks[(i + 1) % philo_count]);
		i++;
	}
}

int	init_forks(t_philo **philosophers, char **argv)
{
	int i;

	i = 0;
	(*philosophers)->data->forks = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_mutex_t));
	if (!((*philosophers)->data->forks))
	{
		printf("Fork Malloc Error");
		return (1);
	}
	while (i < ft_atoi(argv[1]))
	{	
		if(pthread_mutex_init(&((*philosophers)->data->forks[i]), NULL) != 0)
		{
			while(i >= 0)
			{
				pthread_mutex_destroy(&((*philosophers)->data->forks[i]));
				i--;
			}
			pthread_mutex_destroy(&((*philosophers)->data->write_mutex));
			pthread_mutex_destroy(&((*philosophers)->data->death_mutex));
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_other_mutex(t_philo **philosophers)
{
	if (pthread_mutex_init(&((*philosophers)->data->write_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&((*philosophers)->data->death_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&((*philosophers)->data->write_mutex));
		return (1);
	}
	return (0);
}

int	init_data(t_philo **philosophers, char **argv)
{
	(*philosophers)->data = ft_calloc(1, sizeof(t_data));
	if (!(*philosophers)->data)
	{
		free(*philosophers);
		printf("Malloc Error For Data");
		return (1);
	}
	(*philosophers)->data->num_philosophers.num_philosophers = ft_atoi(argv[1]);
	(*philosophers)->data->num_philosophers.time_to_die = ft_atoi(argv[2]);
	(*philosophers)->data->num_philosophers.time_to_eat = ft_atoi(argv[3]);
	(*philosophers)->data->num_philosophers.time_to_sleep = ft_atoi(argv[4]);
	(*philosophers)->data->any_philosopher_died = 0;
	(*philosophers)->data->start_time = get_time();
	if (argv[5])
		(*philosophers)->data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		(*philosophers)->data->number_of_times_each_philosopher_must_eat = -1;
	if (init_other_mutex(philosophers))
		return (-1);
	if (init_forks(philosophers, argv))
		return (-1);
	return (0);
}

int	init_philosophers(char **argv, t_philo **philosophers)
{
	int result;

	*philosophers = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!(*philosophers))
	{
		printf("Malloc Error For Philosophers");
		return (1);
	}
	result = init_data(philosophers, argv);
	if (result == 1)
		return (1);
	else if(result == -1)
	{
		free((*philosophers)->data);
		free(*philosophers);
		return (1);
	}
	fill_philosophers(philosophers, ft_atoi(argv[1]));
	return (0);
}
