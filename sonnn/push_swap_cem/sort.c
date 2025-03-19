#include "push_swap.h"

int	sort(t_tab *str, int len)
{
	int	halfa;

	halfa = 0;
	str->size_b = 0;
	if (check_sorted_a(str, len) == 0)
	{
		if (len == 2)
			sa(str);
		else if (len == 3)
			sort_for_three(str, len);
		else
			sort_main(str, len, halfa);
	}
	return (0);
}

int	sort_main(t_tab *str, int len, int halfa)
{
	int	len2;
	int	count;

	count = 0;
	len2 = len;
	if (check_sorted_a(str, len) == 1)
		return (1);
	else if (len <= 3)
	{
		sort_for_three(str, len);
		return (1);
	}
	if (!(half_number(&halfa, str, len)))
		return (0);
	while (len != (len2 / 2 + len2 % 2))
	{
		if (str->a->content < halfa && (len--))
			pb(str);
		else if (++count)
			ra(str);
	}
	str->size_a = ft_lstsize(str->a);
	while (len2 / 2 + len2 % 2 != str->size_a && count--)
		rra(str);
	return (sort_main(str, (len2 / 2 + len2 % 2), halfa) && sort_b(str, (len2 / 2), 0, 0));
}

void	sort_for_three(t_tab *str, int len)
{
	str->size_a = ft_lstsize(str->a);
	if (str->size_a == 3 && len == 3)
		for_index(0, str);
	else if (len == 2 && str->a->content > str->a->next->content)
		sa(str);
	else if (len == 3)
	{
		while (len != 3 || !(str->a->content < str->a->next->content
				&& str->a->next->content < str->a->next->next->content))
		{
			if (len == 3 && str->a->content > str->a->next->content
				&& str->a->next->next->content)
				sa(str);
			else if (len == 3 && !(str->a->next->next->content > str->a->content
					&& str->a->next->next->content > str->a->next->content))
			{
				pb(str);
				len--;
			}
			else if (str->a->content > str->a->next->content)
				sa(str);
			else if (len++)
				pa(str);
		}
	}
}

void	for_index(int index, t_tab *str)
{
	if ((str->a->next->content > str->a->content)
		&& (str->a->next->content > str->a->next->next->content))
		index = 1;
	else if ((str->a->next->next->content > str->a->content)
		&& (str->a->next->next->content > str->a->next->content))
		index = 2;
	if (index == 0 && (str->a->next->content > str->a->next->next->content))
	{
		sa(str);
		rra(str);
	}
	else if (index == 0)
		ra(str);
	else if (index == 1 && (str->a->content > str->a->next->next->content))
		rra(str);
	else if (index == 1)
	{
		sa(str);
		ra(str);
	}
	else
		if (str->a->content > str->a->next->content)
			sa(str);
}
