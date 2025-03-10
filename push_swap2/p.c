#include "push_swap.h"

void	pa(t_tab *str)
{
    t_list *tmp;

    if (!str->b)
        return;
    tmp = str->b->next;
    str->b->next = str->a;
    str->a = str->b;
    str->b = tmp;
}

void	pb(t_tab *str)
{
    t_list *tmp;

    if (!str->a)
        return;
    tmp = str->a->next;
    str->a->next = str->b;
    str->b = str->a;
    str->a = tmp;
}
