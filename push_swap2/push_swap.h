#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

typedef struct tab
{
	t_list *a;
	t_list *b;
	int size_a;
	int size_b;
	int halfa;
	int halfb;
}	t_tab;


void    sa(t_tab *str);
void    sb(t_tab *str);
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
int 	half_number(int *half, t_tab *str, int len);
int		half_number_b(int *half, t_tab *str, int len);
void	sort_half(int *tmp, int len);
int		check_sorted_a(t_tab *str, int len);
int		check_sorted_b(t_tab *str, int len);
int		sort_for_three(t_tab *str);
int		sort_for_three_b(t_tab *str);
int		sort_b(t_tab *str, int len);
int		sort_main(t_tab *str, int len);

#endif