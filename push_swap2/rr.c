#include "push_swap.h"

void	rra(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->a) || !(str->a)->next)
		return;
	tmp = str->a;
	while (tmp->next)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp->next = (str->a);
	tmp2->next = NULL;
	str->a = tmp;
}

void	rrb(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->b) || !(str->b)->next)
		return;
	tmp = str->b;
	while (tmp->next)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp->next = (str->b);
	tmp2->next = NULL;
	str->b = tmp;
}

void	rrr(t_tab *str)
{
	rra(str);
	rrb(str);
}
