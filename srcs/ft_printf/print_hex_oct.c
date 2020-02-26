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

uintmax_t			unsignedIntArgs(s_fwpls *st)
{
	if (st->specifier == 'p')
		return ((uintmax_t)(uintptr_t)va_arg(st->args, void *));
	else if (st->flags & L_FLAG/* || st->specifier == 'O' || st->specifier == 'U'*/)
		return ((uintmax_t)va_arg(st->args, unsigned long int));
	else if (st->flags & HH_FLAG)
		return ((uintmax_t)(unsigned char)va_arg(st->args, unsigned int));
	else if (st->flags & H_FLAG)
		return ((uintmax_t)(unsigned short int)va_arg(st->args, unsigned int));
	else if (st->flags & LL_FLAG)
		return ((uintmax_t)va_arg(st->args, unsigned long long int));
	else if (st->flags & J_FLAG)	//вывод intmax
		return (va_arg(st->args, uintmax_t));
	else if (st->flags & Z_FLAG)	//вывод size_t
		return ((uintmax_t)va_arg(st->args, size_t)); // вывод size_t
/*	else if (st->flags & T_FLAG)
		return ((uintmax_t)va_arg(st->args, __darwin_ptrdiff_t));*/
	else
		return ((uintmax_t)va_arg(st->args, unsigned int));
}

void			printUnsignedInt(s_fwpls *st)
{
	uintmax_t	nbr;
    int         len;

	st->base = 10;
	nbr = unsignedIntArgs(st);
	len = unbrLen(st, nbr);
	len = (nbr == 0 && st->flags & PRECI_FLAG) ? 0 : len; //если nbr = 0 точкность . ничего не выводить orig printf - (%.d, 0) = ' '
	if (st->flags & PRECI_FLAG)
		st->flags ^= ZERO_FLAG;
	intPadWidth(st, len, 1);
	itoaBase(st, nbr, len);
	if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))
		padWidth(st, MAX(st->precision, len));
}

void			printOct(s_fwpls *st)
{
	uintmax_t	nbr;
	int			len;

	st->base = 8;
	nbr = unsignedIntArgs(st);
	len = nbrLen(st, nbr);
	len = (nbr == 0 && st->flags & PRECI_FLAG && !(st->flags & HASH_FLAG)) ? 0 : len; //если 0 + хаш и !перк = 0 если 0 + хаш и перк = ""
	if (st->flags & PRECI_FLAG) //если есть точность zero flag игнорируется
		st->flags ^= ZERO_FLAG;
	if (st->flags & HASH_FLAG && nbr != 0 && st->precision <= len)
		st->width--;
	intPadWidth(st, len, 0);
	if (st->flags & HASH_FLAG && nbr != 0 && st->precision <= len) //если HASH напечатать 0 перед nbr
		buff(st, "0", 1);
	itoaBase(st, MOD(nbr), len);
	if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))
		padWidth(st, MAX(st->precision, len));
}

void			printHex(s_fwpls *st)
{
	uintmax_t	nbr;
	int			len;

	if (st->specifier == 'p')
		st->flags |= HASH_FLAG;
	st->base = 16;
	nbr = unsignedIntArgs(st);
	st->hex = nbr;
	len = nbrLen(st, nbr);
	len = (nbr == 0 && (st->flags & PRECI_FLAG || (st->flags & HASH_FLAG && st->flags & PRECI_FLAG))) ? 0 : len;
	if (st->flags & PRECI_FLAG) //если есть точность zero flag игнорируется
		st->flags ^= ZERO_FLAG;
	if (st->flags & HASH_FLAG && (nbr != 0 || st->specifier == 'p')) //если #(добавить 0x)
		st->width -= 2;
	intPadWidth(st, len, 0);
	itoaBase(st, MOD(nbr), len);
	if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))
		padWidth(st, MAX(st->precision, len));
}