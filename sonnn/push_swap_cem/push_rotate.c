#include "push_swap.h"

void	ra(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->a) || !str->a->next)
		return ;
	tmp = str->a;
	str->a = str->a->next;
	tmp->next = NULL;
	tmp2 = str->a;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	printf("%s\n", "ra");
}

void	rb(t_tab *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(str->b) || !str->b->next)
		return ;
	tmp = str->b;
	str->b = str->b->next;
	tmp->next = NULL;
	tmp2 = str->b;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	printf("%s\n", "rb");
}

void	rr(t_tab *str)
{
	ra(str);
	rb(str);
}

void	pa(t_tab *str)
{
	t_list	*tmp;

	if (!str->b)
		return ;
	tmp = str->b->next;
	str->b->next = str->a;
	str->a = str->b;
	str->b = tmp;
	str->size_a++;
	str->size_b--;
	printf("%s\n", "pa");
}

void	pb(t_tab *str)
{
	t_list	*tmp;

	if (!str->a)
		return ;
	tmp = str->a->next;
	str->a->next = str->b;
	str->b = str->a;
	str->a = tmp;
	str->size_b++;
	str->size_a--;
	printf("%s\n", "pb");
}
