#include "push_swap.h"

int	sort_half(int *tmp2, int len)
{
	int	i;
	int	j;
	int tmp3;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (&tmp2[i] > &tmp2[j])
			{
				tmp3 = tmp2[i];
				tmp2[i] = tmp2[j];
				tmp2[j] = tmp3;
			}
			j++;
		}
		i++;
	}
	return (*tmp2);
}

int half_number(int *half, t_tab *str, int len)
{
	{
		t_list *tmp;
		int tmp2[1000];
		int i;

		tmp = str->a;
		i = 0;
		while (tmp->next != NULL)
		{
			tmp2[i] = tmp->content;
			tmp = tmp->next;
			i++;
		}
		sort_half(tmp2, len);
		*half = tmp2[(i / 2) + (i % 2)];
		return (1);
	}
}

int sort_b(t_tab *str, int len)
{
	int count;
	int halfb = 0;
	int len2;

	count = 1;
	len2 = len;
	if (check_sorted_b(str, len) == 1)
	{
		while (len-- >= 0)
			pa(str);
		return (1);
	}
	if (len <= 3)
	{
		sort_for_three_b(str);
		return (1);
	}
	if (!half_number_b(&halfb, str, len))
		return (0);
	while (len >= (len2 / 2))
	{
		if (str->b->content >= halfb && len)
		{
			pa(str);
			len--;
		}
		else
		{
			rb(str);
			count++;
		}
	}
	while (count--)
		rrb(str);	
	return(sort_main(str, (len2 / 2 + len2 % 2)) && sort_b(str, (len2 / 2)));
}

int	sort_for_three_b(t_tab *str)
{
	int index;

	index = 0;
	if ((str->b->next->content > str->b->content) && (str->b->next->content > str->b->next->next->content))
		index = 1;
	else if ((str->b->next->next->content > str->b->content) && (str->b->next->next->content > str->b->next->content))
		index = 2;
	if(index == 0)
	{
		if (str->b->next->content > str->b->next->next->content)
		{
			sb(str);
			rrb(str);
		}
		else
			rb(str);
	}
	else if (index == 1)
	{
		if (str->b->content > str->b->next->next->content)
			rrb(str);
		else
		{
			sb(str);
			rrb(str);
		}
	}
	else
	{
		if (str->b->content > str->b->next->content)
			sb(str);
	}
	return (1);
}

int half_number_b(int *half, t_tab *str, int len)
{
	{
		t_list	*tmp;
		int tmp2[1000];
		int i;

		i = 0;
		tmp = str->b;
		while (tmp->next != NULL)
		{
			tmp2[i] = tmp->content;
			tmp = tmp->next;
			i++;
		}
		sort_half(tmp2, len);
		*half = tmp2[i / 2];
		return (1);
	}
}