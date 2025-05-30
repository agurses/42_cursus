/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:07:32 by agurses           #+#    #+#             */
/*   Updated: 2025/03/21 20:04:34 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}			t_list;

typedef struct s_tab
{
	t_list	*a;
	t_list	*b;
	int		size_a;
	int		size_b;
	int		halfa;
	int		halfb;
}	t_tab;

void	sa(t_tab *str);
void	sb(t_tab *str);
void	ss(t_tab *str);
void	pa(t_tab *str);
void	pb(t_tab *str);
void	ra(t_tab *str);
void	rb(t_tab *str);
void	rr(t_tab *str);
void	rra(t_tab *str);
void	rrb(t_tab *str);
void	rrr(t_tab *str);
int		sort(t_tab *str, int len);
int		max_value(t_tab *str);
void	count_sort(t_tab *str, int grade);
int		half_number(int *half, t_tab *str, int len);
int		half_number_b(int *half, t_tab *str, int len);
int		sort_half(int *tmp2, int len);
int		check_sorted_a(t_tab *str, int len);
int		check_sorted_b(t_tab *str, int len);
void	sort_for_three(t_tab *str, int len);
void	sort_for_three_b(t_tab *str, int len);
int		sort_b(t_tab *str, int len, int halfb, int countb);
int		sort_main(t_tab *str, int len, int halfa, int len2);
void	printList(t_list *head);
int		ft_lstsize(t_list *head);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(int content);
long	ft_atoi_swap(const char *str);
void	ft_write_error(char *str);
void	free_list(t_list *lst);
void	free_split(char **split);
int		is_valid_number(char *str);
void	for_index(int index, t_tab *str);
void	for_index_b(t_tab *str, int index, int i);
int		check_push(int len, t_tab *str);
t_list	*ft_create_list(char **arg, int ac, t_tab *str);
t_list	*process_arguments(char **arg, int ac, t_tab *str);
t_list	*validate_and_exit(char **arg, int ac, t_tab *str, t_list *lst);
int		check(int nbr, t_list *lst, char *arg);

#endif