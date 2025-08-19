#include "philo.h"

int	end_simulation(t_philo *philosophers)
{
	int	i;
	int	count;

	count = philosophers->data->num_philosophers.num_philosophers;
	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&(philosophers->data->forks[i]));
	pthread_mutex_destroy(&(philosophers->data->write_mutex));
	pthread_mutex_destroy(&(philosophers->data->death_mutex));
	free(philosophers->data->forks);
	//sem_destroy(&philosophers->data->waiter);
	free(philosophers->data);
	free(philosophers);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILO)
	{
		printf("Undefined Philo Numbers");
		return (1);
	}
	else if (ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 
		|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[3]) > ft_atoi(argv[2]))
	{
		printf("Undefined Timers");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]))
	{
		if (ft_atoi(argv[5]) < 1)
		{
			printf("Error. Undefined Eat Number");
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo *philosophers;

	if (!(argc >=5 && argc <= 6))
	{
		printf("Number Of Bad Arguments\n");
		return (1);
	}
	if (check_args(argc, argv))
		return (1);
	if (init_philosophers(argv, &philosophers))
		return (1);
	start_simulation(philosophers);
	end_simulation(philosophers);
	return (0);
}
