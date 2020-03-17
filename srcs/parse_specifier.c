/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSpecifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:44:47 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/17 14:44:48 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_jump_table(t_jumptable *j_table)
{
	j_table['%'] = &print_percent;
	j_table['c'] = &print_char;
	j_table['C'] = &print_char;
	j_table['s'] = &print_str;
	j_table['S'] = &print_str;
	j_table['p'] = &print_hex;
	j_table['i'] = &print_int;
	j_table['d'] = &print_int;
	j_table['u'] = &print_uint;
	j_table['U'] = &print_uint;
	j_table['o'] = &print_oct;
	j_table['x'] = &print_hex;
	j_table['X'] = &print_hex;
	j_table['f'] = &print_double;
	j_table['F'] = &print_double;
	j_table['b'] = &print_binary;
}

t_jumptable		get_handler_funct(t_var *st)
{
	static t_jumptable	specifier_jt[128] = {NULL};

	if (specifier_jt['%'] == NULL)
		init_jump_table(specifier_jt);
	parse_flags(st);
	parse_lenght(st);
	if (ft_isascii((int)(st->specifier = *st->fmt)))
		return (specifier_jt[(int)st->specifier]);
	else
		return (NULL);
}

void			pad_flags(t_var *st, int print_pl_sp)
{
	int			s;

	s = st->specifier;
	if (st->sign)
		buff(st, "-", 1);
	else if (st->flags & PLUS_F && print_pl_sp && st->specifier != 'u')
		buff(st, "+", 1);
	else if (st->flags & SPACE_F && print_pl_sp && st->specifier != 'u')
		buff(st, " ", 1);
	if ((st->flags & HASH_F && hex(s) && st->hex != 0) || s == 'p')
		buff(st, upp(st->specifier) ? "0X" : "0x", 2);
}

long double		power(int base, int pwr, long double nbr)
{
	uintmax_t	res;

	res = 1;
	if (base == 0)
		return (1);
	while (pwr--)
		res *= base;
	return ((nbr + (uintmax_t)nbr - (uintmax_t)nbr) * res);
}

long double		power_l(int base, int pwr, long double nbr)
{
	uintmax_t	res;

	res = 1;
	while (pwr > 19)
	{
		res *= base;
		pwr--;
	}
	return (power(base, pwr, (nbr - (uintmax_t)nbr) * res));
}
