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


int     		nbrLen(s_fwpls *st, intmax_t n)
{
    int     	intLen;

	intLen = 1;
	while ((n /= st->base) > 0)
        intLen++;
	return (intLen);
}

int     		unbrLen(s_fwpls *st, uintmax_t n)
{
    int     	intLen;

    intLen = 1;
    while ((n /= st->base) > 0)
        intLen++;
    return (intLen);
}

intmax_t		signedIntArgs(s_fwpls *st)
{
	if (st->flags & L_FLAG || st->specifier == 'D')
		return ((intmax_t)va_arg(st->args, signed long));
	else if (st->flags & HH_FLAG)
		return ((intmax_t)(signed char)va_arg(st->args, signed int));
	else if (st->flags & H_FLAG)
		return ((intmax_t)(signed short)va_arg(st->args, signed int));
	else if (st->flags & LL_FLAG)
		return (intmax_t)va_arg(st->args, signed long long);
	else if (st->flags & J_FLAG)
		return (va_arg(st->args, intmax_t));
/*	else if (st->flags & T_FLAG)
		return ((intmax_t)va_arg(st->args, __darwin_ptrdiff_t));*/
	else
		return ((intmax_t)va_arg(st->args, signed int));
}

void			intPadWidth(s_fwpls *st, int totalLen, int printPL_SP) //печать-вывод флагов щирины, int double
{
	int 		widthLen;
	int 		zeroLen;

	widthLen = (st->flags & WIDTH_FLAG) ? MAX(st->precision, totalLen) : totalLen; //для того что бы вычесть макс число из st->width
	zeroLen = (st->precision > totalLen) ? st->precision - totalLen : 0;				//если точность больше длинны числа, заполнить ее 0
	if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
	{
		if (st->flags & ZERO_FLAG)
            widthLen = st->width - widthLen;
		if (st->flags & PRECI_FLAG && (st->specifier != 'f' && st->specifier != 'F')) // со спец f не используется
			padWidth(st, zeroLen + totalLen);
		else if (!(st->flags & ZERO_FLAG))
			padWidth(st, widthLen);
	}
	padFlags(st, printPL_SP);
	if (st->flags & PRECI_FLAG && (st->specifier != 'f' && st->specifier != 'F')) // со спец f не используется
        pad(st, zeroLen, '0');
	else if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
		if (st->flags & ZERO_FLAG)
			pad(st, widthLen, '0');
}

void			printInt(s_fwpls *st)
{
	intmax_t	nbr;
	intmax_t	len;

	st->base = 10;
	nbr = signedIntArgs(st);
	len = nbrLen(st, MOD(nbr));
	st->sign = (nbr < 0) ? 1 : 0;
	len = (nbr == 0 && st->flags & PRECI_FLAG) ? 0 : len; //если nbr = 0 точность . ничего не выводить orig printf - (%.d, 0) = ' '
	if (nbr < 0 || st->flags & PLUS_FLAG || st->flags & SPACE_FLAG)
		st->width--;
	if (st->flags & PRECI_FLAG)
		st->flags ^= ZERO_FLAG;
	intPadWidth(st, len, 1);
	itoaBase(st, MOD(nbr), len);
	if (st->flags & WIDTH_FLAG && st->flags & DASH_FLAG)
		padWidth(st, MAX(st->precision, len));
}