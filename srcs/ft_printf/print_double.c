/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 08:26:12 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/23 08:26:13 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 				ifNAN_INF(long double d)
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

long double			doubleArgs(s_fwpls *st)
{
	long double		nbr;

	if (st->flags & FLOAT_L_FLAG)
		nbr = va_arg(st->args, long double);
	else
		nbr = (long double)va_arg(st->args, double);
	return (nbr);
}

void				invalidDouble(s_fwpls *st, int res)
{
	int 			len;

	(st->flags & ZERO_FLAG) ? st->flags = st->flags ^ ZERO_FLAG : 0;
	len = (res < 0 || st->flags & PLUS_FLAG) ? 4 : 3;
	intPadWidth(st, len, (res > 0 && !(st->flags & SPACE_FLAG)) ? 1 : 0);
	if (res == 2)
		(UPP(st->specifier)) ? buff(st, "NAN", 3) : buff(st, "nan", 3);
	else if (res > 0)
		(UPP(st->specifier)) ? buff(st, "INF", 3) : buff(st, "inf", 3);
	else if (res < 0)
		(UPP(st->specifier)) ? buff(st, "-INF", 4) : buff(st, "-inf", 4);
	if (st->flags & WIDTH_FLAG && st->flags & DASH_FLAG)
		padWidth(st, len);
}

void                countWidth(s_fwpls *st, long double nbr)
{
    if (st->flags & SPACE_FLAG && nbr >= 0)
        st->width--;
    if (st->flags & PLUS_FLAG && nbr >= 0)
        st->width--;
    if (st->precision > 0)
        st->width--;
    else if (st->flags & PRECI_FLAG && st->flags & HASH_FLAG)
        st->width--;
    if (nbr < 0.0)
        st->width--;
}

void				printDouble(s_fwpls *st)
{
	long double		nbr;
	size_t 			intLen;

	st->base = 10;
	nbr = doubleArgs(st);
	st->sign = (nbr < 0) ? 1 : 0;
	intLen = nbrLen(st, MOD(nbr));
	if (ifNAN_INF(nbr))
		invalidDouble(st, ifNAN_INF(nbr));
	else
	{
		if (!(st->flags & PRECI_FLAG) || st->precision < 0) //поумаолчанию точность после . 6 цифр
			st->precision = 6;
		countWidth(st, nbr);
		intPadWidth(st, (int)intLen + st->precision, 1); //intLen + prec длина числа + точность для 1234.6456(кол-во символов)
		convertDouble(st, nbr, intLen);
		if (st->flags & WIDTH_FLAG && st->flags & DASH_FLAG)
			padWidth(st, (int)intLen + st->precision); //intLen + prec длина числа + точность для 1234.6456(кол-во символов)
	}
}