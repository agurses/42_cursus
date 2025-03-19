#include "push_swap.h"

int	sort_half(int *tmp2, int len)
{
	int	i;
	int	j;
	int	tmp3;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (tmp2[i] > tmp2[j])
			{
				tmp3 = tmp2[i];
				tmp2[i] = tmp2[j];
				tmp2[j] = tmp3;
			}
			j++;
		}
		i++;
	}
	tmp2[i] = '\0';
	return (*tmp2);
}

int	sort_b(t_tab *str, int len, int halfb, int countb)
{
	int	len2;

	len2 = len;
	len = check_push(len, str);
	if (len <= 3)
	{
		sort_for_three_b(str, len);
		return (1);
	}
	if (!half_number_b(&halfb, str, len))
		return (0);
	while (len != (len2 / 2))
	{
		if (str->b->content >= halfb && (len--))
			pa(str);
		else if (++countb)
			rb(str);
	}
	while (len2 / 2 != str->size_b && countb--)
		rrb(str);
	return (sort_main(str, (len2 / 2 + len2 % 2), 0) && sort_b(str, (len2 / 2), 0, 0));
}

void	sort_for_three_b(t_tab *str, int len)
{
	str->size_b = ft_lstsize(str->b);
	if (str->size_b == 3 && len == 3)
		for_index_b(str, 0, 0);
	else if (len == 2 && str->b->content < str->b->next->content)
		sb(str);
	else if (len == 3)
	{
		while (len || !(str->a->content < str->a->next->content
				&& str->a->next->content < str->a->next->next->content))
		{
			if (len == 1 && str->a->content > str->a->next->content)
				sa(str);
			else if (len == 1 || (len >= 2
					&& (str->b->content > str->b->next->content))
				|| (len == 3 && str->b->content > str->b->next->next->content))
			{
				pa(str);
				len--;
			}
			else
				sb(str);
		}
	}
}

void	for_index_b(t_tab *str, int index, int i)
{
	if ((str->b->next->content > str->b->content)
		&& (str->b->next->content > str->b->next->next->content))
		index = 1;
	else if ((str->b->next->next->content > str->b->content)
		&& (str->b->next->next->content > str->b->next->content))
		index = 2;
	if (index == 0 && (str->b->next->content < str->b->next->next->content))
	{
		sb(str);
		rb(str);
	}
	else if (index == 1 && (str->b->content > str->b->next->next->content))
		sb(str);
	else if (index == 1)
		rb(str);
	else if (index == 2 && (str->b->content > str->b->next->content))
		rrb(str);
	else if (index == 2)
	{
		sb(str);
		rrb(str);
	}
	while (i++ < 3)
		pa(str);
}
int	check_push(int len, t_tab *str)
{
	if (check_sorted_b(str, len) == 1)
		while (len--)
			pa(str);
	if (len == 1)
		pa(str);
	else if (len == 2)
	{
	if (str->b->content < str->b->next->content)
		sb(str);
	while (len--)
		pa(str);
	}
	return (len);
}
