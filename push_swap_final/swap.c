/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:07:44 by agurses           #+#    #+#             */
/*   Updated: 2025/03/19 18:07:45 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_tab *str)
{
	sa(str);
	sb(str);
}

void	sa(t_tab *str)
{
	t_list	*tmp;

	if (!(str->a) || !((str->a)->next))
		return ;
	tmp = str->a;
	str->a = str->a->next;
	tmp->next = str->a->next;
	str->a->next = tmp;
	printf("%s\n", "sa");
}

void	sb(t_tab *str)
{
	t_list	*tmp;

	if (!(str->b) || !((str->b)->next))
		return ;
	tmp = str->b;
	str->b = str->b->next;
	tmp->next = str->b->next;
	str->b->next = tmp;
	printf("%s\n", "sb");
}
