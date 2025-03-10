#include "push_swap.h"

int sort_main(t_tab *str, int len)
{
	int halfa;
	int len2;
	int count;
	int *tmp;

	tmp = (int *)str->a;
	count = 0;
	len2 = len;
	if (check_sorted_a(str, len) == 1)
		return (1);
	if (len <= 3)
	{
		sort_for_three(str);
		return (1);
	}
	if (!(half_number(&halfa, str, len)))
		return (0);
	while (len != (len2 / 2 + len2 % 2))
	{
		if ((tmp < &halfa) && len)
		{
			pb(str);
			len--;
		}
		else
			ra(str);
			count++;
	}
	while (count--)
		rra(str);
	return ((sort_main(str, (len2 / 2 + len2 % 2))) && (sort_b(str, (len / 2))));
}

int	sort_for_three(t_tab *str)
{
	int index;

	index = 0;
	if (&str->a[1] > &str->a[0] && &str->a[1] > &str->a[2])
		index = 1;
	else if (&str->a[2] > &str->a[0] && &str->a[2] > &str->a[1])
		index = 2;
	if(index == 0)
	{
		if (&str->a[1] > &str->a[2])
		{
			sa(str);
			rra(str);
		}
		else
			ra(str);
	}
	else if (index == 1)
	{
		if (&str->a[0] > &str->a[2])
			rra(str);
		else
		{
			sa(str);
			rra(str);
		}
	}
	else
	{
		if (&str->a[0] > &str->a[1])
			sa(str);
	}
	return (1);
}

int	check_sorted_a(t_tab *str, int len)
{
	int i;

	i = 1;
	while (i < len)
	{
		if (&str->a[i - 1] > &str->a[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_sorted_b(t_tab *str, int len)
{
	int i;

	i = 1;
	while (i < len)
	{
		if (&str[i - 1] > &str[i])
			return (0);
		i++;
	}
	return (1);
}

int	sort(t_tab *str, int len)
{
	if (check_sorted_a(str, len) == 0)
	{
		if (len == 2)
			sa(str);
		else if (len == 3)
			sort_for_three(str);
		else
			sort_main(str, len);
	}
	return (0);
}
