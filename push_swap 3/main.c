#include "push_swap.h"

int	lstsize(t_list *av)
{
	t_list *str;
	int i;

	i = 0;
	str = av;
	while (str != NULL)
	{
		str = str->next;
		i++;
	}
	return (i);
}

int	check(int nbr,t_list *lst, char *arg)
{
	int i;
	t_list *tmp;

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
	while (tmp->next != NULL) 
	{
		if (tmp->content == nbr)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_list *ft_create_list(char **arg)
{
	int nbr;
	t_list *tmp;
	t_list *lst;
	int i;

	i = 0;
	lst = NULL;
	while (arg[i])
	{
		nbr = ft_atoi(arg[i]);
		if ((lst != NULL) && ((nbr > 2147483647) || (nbr < -2147483648) || check(nbr, lst, arg[i]) == 0))
		{
			write(1, "ERROR\n", 6);
			return (0);
		}
		tmp = ft_lstnew(nbr);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}
int	main(int ac,char **av)
{
	t_tab *str;
	char **arg;
	int i;

	i = 0;
	str = malloc(sizeof(t_tab));
	if (!str)
		return (-1);
	if (ac == 1)
		return (0);
	if (ac == 2)
	{
		arg = ft_split(av[1], ' ');
		while (arg[i])
			i++;
		ac = i;
	}
	else
		arg = av + 1;	
	str->a = ft_create_list(arg);
	if (str->a == NULL)
		return(-1);

	str->b = NULL;
	str->size_a = lstsize(str->a);
	str->size_b = 0;
	sort(str, ac);
	printf("%d\n", str->a->content);    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf
	printf("%d\n", str->a->next->content);    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf
	printf("%d\n", str->a->next->next->content);    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf
	printf("%d\n", str->a->next->next->next->content);    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf

	free(str->a);
    free(str->b);
}
