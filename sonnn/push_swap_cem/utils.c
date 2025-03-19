#include "push_swap.h"

int	is_valid_number(char *arg, t_tab *str, int ac)
{
	if (!arg || !*arg)
		return (0);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
		{
			if (ac == 2)
				free_split(&arg);
			free(str);
			write(2, "Error\n", 6);
			exit(1);
		}
		arg++;
	}
	return (1);
}
int	check_sorted_a(t_tab *str, int len)
{
	t_list	*tmp;
	int		i;

	tmp = str->a;
	i = 1;
	if (tmp == NULL)
		return (0);
	while (i < len)
	{
		if (tmp->content > tmp->next->content)
			return (0);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	check_sorted_b(t_tab *str, int len)
{
	t_list	*tmp;
	int		i;

	tmp = str->b;
	i = 1;
	if (tmp == NULL || tmp->next == NULL)
		return (1);
	while (i < len)
	{
		if (tmp->content < tmp->next->content)
			return (0);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	half_number(int *half, t_tab *str, int len)
{
	t_list	*tmp;
	int		*tmp2;
	int		i;

	tmp2 = malloc(sizeof(int) * 1000);
	if (tmp2 == NULL)
	{	
		free(tmp2);
		return (0);
	}
	i = 0;
	tmp = str->a;
	while (tmp != NULL && i < len)
	{
		tmp2[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	sort_half(tmp2, len);
	*half = tmp2[(i / 2)];
	free(tmp2);
	return (1);
}
int	half_number_b(int *half, t_tab *str, int len)
{
	t_list	*tmp;
	int		*tmp2;
	int		i;

	tmp2 = malloc(sizeof(int) * 1000);
	if (tmp2 == NULL)
	{	
		free(tmp2);
		return (0);
	}
	i = 0;
	tmp = str->b;
	while (tmp != NULL && i < len)
	{
		tmp2[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	sort_half(tmp2, len);
	*half = tmp2[i / 2];
	free(tmp2);
	return (1);
}
