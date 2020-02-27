/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 09:46:53 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/18 09:46:54 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printChar(s_fwpls *st)
{
	char 	c;

	if (st->flags & L_FLAG || st->specifier == 'C')
		printWChar(st);
	else
	{
		c = (char)va_arg(st->args, int);
		if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
			padWidth(st, 1);
		buff(st, &c, 1);
		if (st->flags & WIDTH_FLAG && st->flags & DASH_FLAG)
			padWidth(st, 1);
	}
}

void		printStr(s_fwpls *st)
{
	char 	*str;
	int 	slen;

	if (st->flags & L_FLAG || st->specifier == 'S')
		printWStr(st);
	else
	{
		if ((str = (char *) va_arg(st->args, char *)) == NULL)
			str = "(null)";
		slen = ft_strlen(str);
		if (st->precision < 0)
			st->precision = slen;
		st->precision = (st->precision > slen) ? slen : st->precision;	// если точность больше лена, верни лен (чтобы отправить правильный nbyte в pad)
		slen = (st->flags & PRECI_FLAG) ? st->precision : slen;		    //если флаг есть точность меняем на лен
		if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))		//если нет флага -, напечатать ' '
			padWidth(st, slen);
		buff(st, str, slen);
		if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))		//если есть флаг -, напечатать specifier затем ' '
			padWidth(st, slen);
	}
}