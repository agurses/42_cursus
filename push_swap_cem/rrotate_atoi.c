#include "push_swap.h"

void	rra(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->a) || !(str->a)->next)
		return ;
	tmp = str->a;
	while (tmp->next)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp->next = (str->a);
	tmp2->next = NULL;
	str->a = tmp;
	str->prcscount++;
	printf("%s\n", "rra");
}

void	rrb(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->b) || !(str->b)->next)
		return ;
	tmp = str->b;
	while (tmp->next)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp->next = (str->b);
	tmp2->next = NULL;
	str->b = tmp;
	str->prcscount++;
	printf("%s\n", "rrb");
}

void	rrr(t_tab *str)
{
	rra(str);
	rrb(str);
}
int	ft_atoi_swap(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if ((result > 2147483648 && sign == -1)
		|| (result > 2147483647 && sign == 1))
		error();
	return (result * sign);
}
void	error()
{

	write(2, "Error\n", 6);
	exit(1);
}
