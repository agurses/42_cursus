#include "minitalk.h"

void	send_char(int pid, char c)
{
	int bit;
	static int i;

	if (i < 32)
	{
		usleep(400);
		i++;
	}
	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit++;
	}
	return ;
}

int	main(int ac, char **av)
{
	int		pid;
	char	*message;
	int		pid_client;
	char	*pid_client_str;

	if (ac != 3)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	pid_client = getpid();
	printf("PID: %d\n", pid_client);
	pid_client_str = ft_itoa(pid_client);
	printf("PID: %s\n", pid_client_str);

	pid = ft_atoi(av[1]);

	while (*pid_client_str)
	{
		send_char(pid, *pid_client_str);
		pid_client_str++;
	}
	send_char(pid, '\n');
	message = av[2];
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
	return (0);
}
