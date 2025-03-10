#include "push_swap.h"

void	sort_half(int *tmp, int len)
{
	int	i;
	int	j;
	int	tmp2;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (&tmp[i] > &tmp[j])
			{
				tmp2 = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = tmp2;
			}
			j++;
		}
		i++;
	}
}

int half_number(int *half, t_tab *str, int len)
{
	{
		t_list	*tmp;
		int tmp2[1000];
		int i;

		i = 0;
		tmp = malloc(len * sizeof(t_list));
		if (!tmp)
			return (0);
		tmp = str->a;
		while (tmp->next != NULL)
		{
			tmp2[i] = *(int *)&tmp;
			tmp = tmp->next;
			i++;
		}
		sort_half(tmp2, len);
		*half = tmp2[len / 2];
		free(tmp);
		return (1);
	}
}

int sort_b(t_tab *str, int len)
{
	int count;
	int halfb;
	int len2;

	count = 0;
	len2 = len;
	if (check_sorted_b(str, len) == 1)
	{
		while (len--)
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
		if (*(int *)&str->b[0] >= halfb && len)
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
	if (&str->b[1] > &str->b[0] && &str->b[1] > &str->b[2])
		index = 1;
	else if (&str->b[2] > &str->b[0] && &str->b[2] > &str->b[1])
		index = 2;
	if(index == 0)
	{
		if (&str->b[1] > &str->b[2])
		{
			sb(str);
			rrb(str);
		}
		else
			rb(str);
	}
	else if (index == 1)
	{
		if (&str->b[0] > &str->b[2])
			rrb(str);
		else
		{
			sb(str);
			rrb(str);
		}
	}
	else
	{
		if (&str->b[0] > &str->b[1])
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
		tmp = malloc(len * sizeof(t_list));
		if (!tmp)
			return (0);
		tmp = str->b;
		while (tmp->next != NULL)
		{
			tmp2[i] = *(int *)&tmp;
			tmp = tmp->next;
			i++;
		}
		sort_half(tmp2, len);
		*half = tmp2[len / 2];
		free(tmp);
		return (1);
	}
}