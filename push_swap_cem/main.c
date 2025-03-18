#include "push_swap.h"

int	check(int nbr, t_list *lst, char *arg)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (arg[i])
	{
		if (!(((arg[i] == '-' || arg[i] == '+') && ft_isdigit(arg[i + 1])
					&& (i == 0 || !ft_isdigit(arg[i - 1])))
				|| ft_isdigit(arg[i])))
			return (0);
		i++;
	}
	if (tmp->content == nbr)
			return (0);
	while (tmp->next != NULL)
	{
		if (tmp->content == nbr)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_valid_number(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_list	*ft_create_list(char **arg, int ac, t_tab *str)
{
	t_list	*tmp;
	t_list	*lst;
	int		i;
	long	nbr;

	i = 0;
	lst = NULL;
	if (!is_valid_number(arg[0]))
	{
		if (ac == 2)
			free_split(arg);
		free(str);
		write(2, "Error\n", 6);
		exit(1);
	}
	while (arg[i])
	{

		nbr = ft_atoi_swap(arg[i]);
		if (((lst != NULL) && (check(nbr, lst, arg[i]) == 0)) || nbr == 2147483649)
		{
			if (ac == 2)
				free_split(arg);
			free_list(lst);
			free(str);
			write(2, "Error\n", 6);
			exit(1);
		}
		tmp = ft_lstnew(nbr);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_split(char **split)
{
    int	i;

    if (!split)
        return;
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void	print_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%d\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_tab	*str;

	str = malloc(sizeof(t_tab));
	if (!str)
		return (-1);
	if (ac == 1)
		return (0);
	av++;
	if (ac == 2)
		av = ft_split(*av, ' ');
	str->a = ft_create_list(av, ac, str);
	if (ac == 2)
		free_split(av);
	if (str->a == NULL)
		{
			free(str);
			return (-1);
		}
	str->prcscount = 0;
	str->b = NULL;
	str->size_a = ft_lstsize(str->a);
	str->size_b = 0;
	sort(str, str->size_a);
	free_list(str->a);
	free_list(str->b);
	free(str);
	return (1);
}
