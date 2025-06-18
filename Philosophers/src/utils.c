#include "philo.h"

long	ft_atoi(const char *str)
{
	long result;
	int i;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '+')
		i++;
	if(str[i] == '-')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			i++;
			if (result > 2147483648)
				break;
			}
		else
			return(-1);
	}
	return (result);
}

void *ft_calloc(size_t count, size_t size)
{
	char *str;
	size_t i;

	str = malloc(count * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

//void        print_status(t_data *data, int id, char *status)
//{
//
//}
//
//int         error_exit(char *str)
//{
//
//}
//