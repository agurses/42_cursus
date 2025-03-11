#include "push_swap.h"


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

int sort_main(t_tab *str, int len)
{
	int halfa = 0;
	int len2;
	int count;

	count = 1;
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
	printf("%d\n", halfa);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
	printf("%d\n", len);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	while (len != (len2 / 2 + len2 % 2) && (count <= len / 2))
	{
		printf("%d\n", halfa);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
		printf("%d\n", str->a->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

		if ((str->a->content <= halfa))
		{
			printf("%s\n", "cemmm");	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

			pb(str);
			len--;
		}
		else
		{
			ra(str);
			count++;
		}
		printf("%d\n", str->a->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
		printf("%d\n", str->a->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
		printf("%d\n", str->a->next->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
		printf("%d\n", str->a->next->next->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
	
	}
	while (count-- >= 0)
		rra(str);
	printf("%d\n", str->a->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
	printf("%d\n", str->a->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
	printf("%d\n", str->a->next->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf
	printf("%d\n", str->a->next->next->next->content);	fflush(stdout);		//uysdjhfgahksjdfhgsadhfghasgdfhlgasdfgasdgf

	return ((sort_main(str, (len2 / 2 + len2 % 2))) && (sort_b(str, (len / 2))));
}

int	sort_for_three(t_tab *str)
{
	int index;

	index = 0;
	if ((str->a->next->content > str->a->content) && (str->a->next->content > str->a->next->next->content))
		index = 1;
	else if ((str->a->next->next->content > str->a->content) && (str->a->next->next->content > str->a->next->content))
		index = 2;
	if(index == 0)
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
			rra(str);
		}
	}
	else
	{
		if (str->a->content > str->a->next->content)
			sa(str);
	}
	return (1);
}

int	check_sorted_a(t_tab *str, int len)
{
	int i;
	t_list *tmp;

	tmp = str->a;
	i = 0;
	while (i++ < len)
	{
		if (tmp->content > tmp->next->content)
			return (0);
		i++;
	}
	return (1);
}

int	check_sorted_b(t_tab *str, int len)
{
	int i;
	t_list *tmp;

	tmp = str->b;
	i = 0;
	printf("%s\n", "cem");    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf
	
	if (str->b == NULL)
		return (0);
	printf("%s\n", "cem");    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf
	
	if (tmp->next == NULL)
		return (0);
	if(tmp->next == NULL)
		return(0);
	printf("%s\n", "cem");    fflush(stdout); //sahdfglksadjgfjahsdfjhsdhfjasdjfhsdf

	while (i++ < len)
	{
		if (tmp->content > tmp->next->content)
			return (0);
		i++;
	}
	return (1);
}
