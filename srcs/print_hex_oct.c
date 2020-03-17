/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_oct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 08:22:50 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/20 08:22:53 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		u_int_args(t_var *st)
{
	if (st->specifier == 'p')
		return ((uintmax_t)(uintptr_t)va_arg(st->args, void *));
	else if (st->flags & L_FLAG || st->specifier == 'U')
		return ((uintmax_t)va_arg(st->args, unsigned long int));
	else if (st->flags & LL_FLAG || st->specifier == 'U')
		return ((uintmax_t)va_arg(st->args, unsigned long long int));
	else if (st->flags & HH_FLAG)
		return ((uintmax_t)(unsigned char)va_arg(st->args, unsigned int));
	else if (st->flags & H_FLAG)
		return ((uintmax_t)(unsigned short int)va_arg(st->args, unsigned int));
	else if (st->flags & J_FLAG)
		return (va_arg(st->args, uintmax_t));
	else if (st->flags & Z_FLAG)
		return ((uintmax_t)va_arg(st->args, size_t));
	else
		return ((uintmax_t)va_arg(st->args, unsigned int));
}

void			print_uint(t_var *st)
{
	uintmax_t	nbr;
	int			len;

	st->base = 10;
	nbr = u_int_args(st);
	len = unbr_len(st, nbr);
	len = (nbr == 0 && st->flags & PRECI_F) ? 0 : len;
	if (st->flags & PRECI_F)
		st->flags ^= ZERO_F;
	nbr_pad_width(st, len, 1);
	itoa_base(st, nbr, len);
	if (st->flags & WIDTH_F && (st->flags & DASH_F))
		pad_width(st, max(st->precision, len));
}

void			print_oct(t_var *st)
{
	uintmax_t	nbr;
	int			len;
	int			f;

	f = st->flags;
	st->base = 8;
	nbr = u_int_args(st);
	len = unbr_len(st, nbr);
	len = (nbr == 0 && f & PRECI_F && !(f & HASH_F)) ? 0 : len;
	if (st->flags & PRECI_F)
		st->flags ^= ZERO_F;
	if (st->flags & HASH_F && nbr != 0 && st->precision <= len)
		st->width--;
	nbr_pad_width(st, len, 0);
	if (st->flags & HASH_F && nbr != 0 && st->precision <= len)
		buff(st, "0", 1);
	itoa_base(st, nbr, len);
	if (st->flags & WIDTH_F && (st->flags & DASH_F))
		pad_width(st, max(st->precision, len));
}

void			print_hex(t_var *st)
{
	uintmax_t	nbr;
	int			len;
	int			f;

	f = st->flags;
	if (st->specifier == 'p')
		st->flags |= HASH_F;
	st->base = 16;
	nbr = u_int_args(st);
	st->hex = nbr;
	len = unbr_len(st, nbr);
	len = (nbr == 0 && (f & PRECI_F || (f & HASH_F && f & PRECI_F))) ? 0 : len;
	if (st->flags & PRECI_F)
		st->flags ^= ZERO_F;
	if (st->flags & HASH_F && (nbr != 0 || st->specifier == 'p'))
		st->width -= 2;
	nbr_pad_width(st, len, 0);
	itoa_base(st, nbr, len);
	if (st->flags & WIDTH_F && (st->flags & DASH_F))
		pad_width(st, max(st->precision, len));
}
