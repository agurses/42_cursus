#include "push_swap.h"

int	sort(t_tab *str, int len)
{
	if (check_sorted_a(str, len) == 0)
	{
		if (len == 2)
			sa(str);
		else if (len == 3)
			sort_for_three(str, len);
		else
			sort_main(str, len);
	}
	return (0);
}

int	sort_main(t_tab *str, int len)
{
	int	halfa;
	int	len2;
	int	count;

	count = 0;
	halfa = 0;
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
	return (sort_main(str, (len2 / 2 + len2 % 2)) && sort_b(str, (len2 / 2)));
}

void	sort_for_three(t_tab *str, int len)
{
	int	index;

	str->size_a = ft_lstsize(str->a);
	if (str->size_a == 3 && len == 3)
	{
		index = 0;
		if ((str->a->next->content > str->a->content)
			&& (str->a->next->content > str->a->next->next->content))
			index = 1;
		else if ((str->a->next->next->content > str->a->content)
			&& (str->a->next->next->content > str->a->next->content))
			index = 2;
		if (index == 0)
		{
			if (str->a->next->content > str->a->next->next->content)
			{
				sa(str);
				rra(str);
			}
			else
				ra(str);
		}
		else if (index == 1)
		{
			if (str->a->content > str->a->next->next->content)
				rra(str);
			else
			{
				sa(str);
				ra(str);
			}
		}
		else
			if (str->a->content > str->a->next->content)
				sa(str);
	}
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
