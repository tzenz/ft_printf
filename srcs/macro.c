/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:55:45 by tzenz             #+#    #+#             */
/*   Updated: 2020/03/03 08:55:47 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				hex(char c)
{
	if (c == 'x' || c == 'X' || c == 'p')
		return (1);
	else
		return (0);
}

int				upp(char c)
{
	if (c == 'X' || c == 'F')
		return (1);
	else
		return (0);
}

long double		mod(long double i)
{
	if (i < 0)
		return (i * -1);
	else
		return (i);
}

intmax_t		max(intmax_t a, intmax_t b)
{
	return ((a > b)) ? a : b;
}

long double		f_mod(long double a)
{
	if (a < 0.0f)
		return (a * -1);
	else
		return (a);
}
