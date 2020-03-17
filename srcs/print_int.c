/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:15:28 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/19 15:15:29 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				nbr_len(t_var *st, intmax_t n)
{
	int			int_len;

	int_len = 1;
	while ((n /= st->base) > 0)
		int_len++;
	return (int_len);
}

int				unbr_len(t_var *st, uintmax_t n)
{
	int			int_len;

	int_len = 1;
	while ((n /= st->base) > 0)
		int_len++;
	return (int_len);
}

intmax_t		int_args(t_var *st)
{
	if (st->flags & L_FLAG || st->specifier == 'D')
		return ((intmax_t)va_arg(st->args, signed long));
	else if (st->flags & LL_FLAG)
		return (intmax_t)va_arg(st->args, signed long long);
	else if (st->flags & J_FLAG)
		return (va_arg(st->args, intmax_t));
	else if (st->flags & Z_FLAG)
		return ((intmax_t)va_arg(st->args, size_t));
	else if (st->flags & HH_FLAG)
		return ((intmax_t)(signed char)va_arg(st->args, signed int));
	else if (st->flags & H_FLAG)
		return ((intmax_t)(signed short)va_arg(st->args, signed int));
	else
		return ((intmax_t)va_arg(st->args, signed int));
}

void			nbr_pad_width(t_var *st, int len, int print_pl_sp)
{
	int			width_len;
	int			zero_len;
	int			spec;

	spec = st->specifier;
	width_len = (st->flags & WIDTH_F) ? max(st->precision, len) : len;
	zero_len = (st->precision > len) ? st->precision - len : 0;
	if (st->flags & WIDTH_F && !(st->flags & DASH_F))
	{
		if (st->flags & ZERO_F)
			width_len = st->width - width_len;
		if (st->flags & PRECI_F && (spec != 'f' && spec != 'F'))
			pad_width(st, zero_len + len);
		else if (!(st->flags & ZERO_F))
			pad_width(st, width_len);
	}
	pad_flags(st, print_pl_sp);
	if (st->flags & PRECI_F && (st->specifier != 'f' && st->specifier != 'F'))
		pad(st, zero_len, '0');
	else if (st->flags & WIDTH_F && !(st->flags & DASH_F))
		if (st->flags & ZERO_F)
			pad(st, width_len, '0');
}

void			print_int(t_var *st)
{
	intmax_t	nbr;
	intmax_t	len;

	nbr = int_args(st);
	st->base = 10;
	st->sign = (nbr < 0) ? 1 : 0;
	len = nbr_len(st, mod(nbr));
	len = (nbr == 0 && st->flags & PRECI_F) ? 0 : len;
	if (nbr < 0 || st->flags & PLUS_F || st->flags & SPACE_F)
		st->width--;
	st->precision = (st->precision < 0) ? st->width : st->precision;
	if (st->flags & PRECI_F && st->precision > 0)
		st->flags ^= ZERO_F;
	nbr_pad_width(st, len, 1);
	itoa_base(st, mod(nbr), len);
	if (st->flags & WIDTH_F && st->flags & DASH_F)
		pad_width(st, max(st->precision, len));
}
