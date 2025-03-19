/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:07:13 by agurses           #+#    #+#             */
/*   Updated: 2025/03/19 21:29:28 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check(int nbr, t_list *lst, char *arg)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (arg[i])
	{
		if (!(((arg[i] == '-' || arg[i] == '+') && ft_isdigit(arg[i + 1])
					&& (i == 0 || !ft_isdigit(arg[i - 1])))
				|| ft_isdigit(arg[i])))
			return (0);
		i++;
	}
	if (tmp->content == nbr)
		return (0);
	while (tmp->next != NULL)
	{
		if (tmp->content == nbr)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

int	main(int ac, char **av)
{
	t_tab	*str;

	str = malloc(sizeof(t_tab));
	if (!str)
		return (-1);
	if (ac == 1)
		return (0);
	av++;
	if (ac == 2)
		av = ft_split(*av, ' ');
	str->a = ft_create_list(av, ac, str);
	if (ac == 2)
		free_split(av);
	if (str->a == NULL)
	{
		free(str);
		return (-1);
	}
	str->b = NULL;
	str->size_a = ft_lstsize(str->a);
	sort(str, str->size_a);
	free_list(str->a);
	free_list(str->b);
	free(str);
	return (1);
}
