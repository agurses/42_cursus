#include "push_swap.h"

void	ra(t_tab *str)
{
	t_list *tmp;
	t_list *tmp2;

	if (!(str->a) || !str->a->next)
		return;
	tmp = str->a;
	str->a = str->a->next;
	tmp->next = NULL;
	tmp2 = str->a;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;    
}

void	rb(t_tab *str)
{
	t_list *tmp;
	t_list *tmp2;

	if (!(str->b) || !str->b->next)
		return;
	tmp = str->b;
	str->b = str->b->next;
	tmp->next = NULL;
	tmp2 = str->b;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;    
}

void	rr(t_tab *str)
{
	ra(str);
	rb(str);
}
