#include "minitalk.h"

void	processor(int sig)
{
	static char	c;
	static int	bit;
	static int	i;
	static int	pid;

	if (sig == SIGUSR1)
		c |= 1 << bit;
	bit++;
	i++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			printf("\nPID: \n%d\n", pid);
			write(1, "\nMessage received\n", 17);
		}
		else
		{
			if (i < 48)
			{
				pid = pid * 10 + (c - '0');
			}
			else
				write(1, &c, 1);
		}
		bit = 0;
		c = 0;
	}

}

int	main(void)
{
	write(1, "\n", 1);
	if (signal(SIGUSR1, processor) == SIG_ERR || signal(SIGUSR2, processor) == SIG_ERR)
	{
		printf("Error\n");
		return (0);
	}
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (1);
}
