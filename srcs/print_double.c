/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 08:26:12 by kkatelyn          #+#    #+#             */
/*   Updated: 2020/02/23 08:26:13 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					if_nan_inf(long double d)
{
	union u_union	u;

	u.d = (double)d;
	if (u.l == 0x7FF8000000000000ll || u.l == 0xFFF8000000000000ll)
		return (2);
	else if (u.l == 0x7FF0000000000000ll)
		return (1);
	else if (u.l == 0xFFF0000000000000ll)
		return (-1);
	return (0);
}

long double			double_args(t_var *st)
{
	long double		nbr;

	if (st->flags & FLOAT_L_FLAG)
		nbr = va_arg(st->args, long double);
	else
		nbr = (long double)va_arg(st->args, double);
	return (nbr);
}

void				invalid_double(t_var *st, int res)
{
	int				len;

	(st->flags & ZERO_F) ? st->flags = st->flags ^ ZERO_F : 0;
	len = (res < 0 || st->flags & PLUS_F) ? 4 : 3;
	nbr_pad_width(st, len, (res > 0 && !(st->flags & SPACE_F)) ? 1 : 0);
	if (res == 2)
		(upp(st->specifier)) ? buff(st, "NAN", 3) : buff(st, "nan", 3);
	else if (res > 0)
		(upp(st->specifier)) ? buff(st, "INF", 3) : buff(st, "inf", 3);
	else if (res < 0)
		(upp(st->specifier)) ? buff(st, "-INF", 4) : buff(st, "-inf", 4);
	if (st->flags & WIDTH_F && st->flags & DASH_F)
		pad_width(st, len);
}

void				count_width(t_var *st, long double nbr)
{
	if (st->flags & SPACE_F && nbr >= 0)
		st->width--;
	if (st->flags & PLUS_F && nbr >= 0)
		st->width--;
	if (st->precision > 0)
		st->width--;
	else if (st->flags & PRECI_F && st->flags & HASH_F)
		st->width--;
	if (nbr < 0.0)
		st->width--;
}

void				print_double(t_var *st)
{
	long double		nbr;
	size_t			int_len;

	st->base = 10;
	nbr = double_args(st);
	st->sign = (nbr < 0) ? 1 : 0;
	int_len = nbr_len(st, mod(nbr));
	if (if_nan_inf(nbr))
		invalid_double(st, if_nan_inf(nbr));
	else
	{
		if (!(st->flags & PRECI_F) || st->precision < 0)
			st->precision = 6;
		count_width(st, nbr);
		nbr_pad_width(st, (int)int_len + st->precision, 1);
		convert_dbl(st, nbr, int_len);
		if (st->flags & WIDTH_F && st->flags & DASH_F)
			pad_width(st, (int)int_len + st->precision);
	}
}
