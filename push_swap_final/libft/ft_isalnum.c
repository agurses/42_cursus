/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:26:02 by agurses           #+#    #+#             */
/*   Updated: 2024/11/15 17:07:42 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int x)
{
	if ((x > 47 && x < 58) || (x > 64 && x < 91) || (x > 96 && x < 123))
		return (1);
	return (0);
}
