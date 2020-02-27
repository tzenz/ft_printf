/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:15:14 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/18 16:15:16 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		putW(s_fwpls *st, int c)
{
	buff(st, &c, 1);
}

void		conversion(s_fwpls *st, int wc)
{
	if (wc <= 0x7f)
		buff(st, &wc, 1);
	else if (wc <= 0x07FF)
	{
		putW(st, (wc >> 6) | 0xC0);		//C0 - 11000000 для 3 октета (указывает кол-во октетов)
		putW(st, (wc & 0x3F) | 0x80);	//3f - 00111111 для 4 октета (обнулить все биты кроме последних 6) / 80 - 10000000 (добавить префикс Unicode)
	}
	else if (wc <= 0xFFFF)
	{
		putW(st, (wc >> 12) | 0xE0);	//E0 - 11100000 для 2 октета (указывает кол-во октетов)
		putW(st, ((wc >> 6) & 0x3F) | 0x80);
		putW(st, (wc & 0x3F) | 0x80);
	}
	else if (wc <=0x10FFFF)
	{
		putW(st, (wc >> 24) | 0xF0);	//F0 - 11110000 для 1 октета (указывает кол-во октетов)
		putW(st, ((wc >> 12) & 0x3F) | 0x80);
		putW(st, ((wc >> 6) & 0x3F) | 0x80);
		putW(st, (wc & 0x3F) | 0x80);
	}
}

size_t		wStrLen(wchar_t *wstr)
{
	size_t	wCharLen;

	wCharLen = 0;
	while (*(wstr++) != L'\0')
		wCharLen++;
	return (wCharLen);
}

void		printWChar(s_fwpls *st)
{
    if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
        padWidth(st, 1);
    conversion(st, (int)va_arg(st->args, int));
    if (st->flags & WIDTH_FLAG && st->flags & DASH_FLAG)
        padWidth(st, 1);
}

void		printWStr(s_fwpls *st)
{
    wchar_t *wstr;
    size_t 	wslen;

    if ((wstr = va_arg(st->args, wchar_t *)) == NULL)
        wstr = L"(null)";
    wslen = wStrLen(wstr);
    if (st->precision < 0)
        st->precision = wslen;
    st->precision = (st->precision > wslen) ? (int)wslen : st->precision;
    wslen = (st->flags & PRECI_FLAG) ? st->precision : wslen;
    if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
        padWidth(st, wslen);
    while (*wstr && wslen--)
        conversion(st, *(wstr++));
    if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))
        padWidth(st, wslen);
}