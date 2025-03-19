/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:47:21 by agurses           #+#    #+#             */
/*   Updated: 2025/03/19 20:42:41 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*validate_and_exit(char **arg, int ac, t_tab *str, t_list *lst)
{
	if (ac == 2)
		free_split(arg);
	free_list(lst);
	free(str);
	write(2, "Error\n", 6);
	exit(1);
}

t_list	*process_arguments(char **arg, int ac, t_tab *str)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;
	long	nbr;

	lst = NULL;
	i = 0;
	while (arg[i])
	{
		nbr = ft_atoi_swap(arg[i]);
		if (((lst != NULL) && (check(nbr, lst, arg[i]) == 0))
			|| nbr == 2147483649)
			validate_and_exit(arg, ac, str, lst);
		tmp = ft_lstnew(nbr);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}

t_list	*ft_create_list(char **arg, int ac, t_tab *str)
{
	if (!is_valid_number(arg[0]))
		validate_and_exit(arg, ac, str, NULL);
	return (process_arguments(arg, ac, str));
}
