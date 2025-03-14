#include "push_swap.h"

int	sort_half(int *tmp2, int len)
{
	printf("%s\n", "sort half başı");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	int	i;
	int	j;
	int tmp3;

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

int half_number(int *half, t_tab *str, int len)
{
	printf("%s\n", "half_number başı");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	{
		t_list *tmp;
		int tmp2[1000];
		int i;

		i = 0;
		tmp = str->a;
		while (tmp != NULL && i < len)
		{
			tmp2[i] = tmp->content;
			tmp = tmp->next;
			i++;
		}
		sort_half(tmp2, len);
		*half = tmp2[(i / 2)];
		return (1);
	}
}

int sort_b(t_tab *str, int len)
{
	int count;
	int halfb = 0;
	int len2;

	printf("%s\n", "sort b başı");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	count = 0;
	len2 = len;
	if (check_sorted_b(str, len) == 1)
	{
		while (len--)
			pa(str);
	}
	if (len == 1)
		pa(str);
	else if (len == 2)
	{
		if (str->b->content < str->b->next->content)
			sb(str);
		while (len--)
			pa(str);
	}
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
		{
			pa(str);
		}
		else if(++count)
		{
			rb(str);
		}
	}
	while (len2 / 2 != str->size_b && count--)
		rrb(str);		
	return(sort_main(str, (len2 / 2 + len2 % 2)) && sort_b(str, (len2 / 2)));
}

void	sort_for_three_b(t_tab *str, int len)
{
	int index;
	int i;

	printf("%s\n", "sort_for_three_b başı");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	i = 0;
	str->size_b = ft_lstsize(str->b);
	if (str->size_b == 3 && len == 3)
	{
		index = 0;
		if ((str->b->next->content > str->b->content) && (str->b->next->content > str->b->next->next->content))
			index = 1;
		else if ((str->b->next->next->content > str->b->content) && (str->b->next->next->content > str->b->next->content))
			index = 2;
		if(index == 0)
		{
			printf("%s\n", "index 0 b");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

			if (str->b->next->content < str->b->next->next->content)
			{
				sb(str);
				rb(str);
			}

		}
		else if (index == 1)
		{							
			printf("%s\n", "index 1 b");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

			if (str->b->content > str->b->next->next->content)
				sb(str);
			else
			{
				rb(str);
			}
		}
		else
		{
			printf("%s\n", "index 2 b");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
			if (str->b->content > str->b->next->content)
				rrb(str);
			else
			{
				sb(str);
				rrb(str);
			}

		}
		while (i++ < 3)	
			pa(str);
	}
	else if (len == 2 && str->b->content > str->b->next->content)
		sb(str);
	else if (len == 3)
	{
		while (len || !(str->a->content < str->a->next->content
				&& str->a->next->content < str->a->next->next->content))
		{
			
			if (len == 1 && str->a->content > str->a->next->content)
				sa(str);
			else if (len == 1 || (len >= 2 && (str->b->content > str->b->next->content)) 
					|| (len == 3 && str->b->content > str->b->next->next->content))
				{pa(str);
				len--;}
			else
				sb(str);
		}
	}
}

int half_number_b(int *half, t_tab *str, int len)
{
	{
		printf("%s\n", "half_number_b başı");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
		t_list	*tmp;
		int tmp2[1000];
		int i;

		i = 0;
		tmp = str->b;
		while (tmp != NULL && i < len)
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
