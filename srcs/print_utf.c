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

void		print_w(t_var *st, int c)
{
	buff(st, &c, 1);
}

void		conversion(t_var *st, int wc)
{
	if (wc <= 0x7f)
		buff(st, &wc, 1);
	else if (wc <= 0x07FF)
	{
		print_w(st, (wc >> 6) | 0xC0);
		print_w(st, (wc & 0x3F) | 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		print_w(st, (wc >> 12) | 0xE0);
		print_w(st, ((wc >> 6) & 0x3F) | 0x80);
		print_w(st, (wc & 0x3F) | 0x80);
	}
	else if (wc <= 0x10FFFF)
	{
		print_w(st, (wc >> 24) | 0xF0);
		print_w(st, ((wc >> 12) & 0x3F) | 0x80);
		print_w(st, ((wc >> 6) & 0x3F) | 0x80);
		print_w(st, (wc & 0x3F) | 0x80);
	}
}

size_t		w_strlen(wchar_t *wstr)
{
	size_t	wchar_len;

	wchar_len = 0;
	while (*(wstr++) != L'\0')
		wchar_len++;
	return (wchar_len);
}

void		print_wchar(t_var *st)
{
	if (st->flags & WIDTH_F && !(st->flags & DASH_F))
		pad_width(st, 1);
	conversion(st, (int)va_arg(st->args, int));
	if (st->flags & WIDTH_F && st->flags & DASH_F)
		pad_width(st, 1);
}

void		print_wstr(t_var *st)
{
	wchar_t *wstr;
	size_t	wslen;

	if ((wstr = va_arg(st->args, wchar_t *)) == NULL)
		wstr = L"(null)";
	wslen = w_strlen(wstr);
	if (st->precision < 0)
		st->precision = wslen;
	st->precision = (st->precision > (int)wslen) ? (int)wslen : st->precision;
	wslen = (st->flags & PRECI_F) ? st->precision : wslen;
	if (st->flags & WIDTH_F && !(st->flags & DASH_F))
		pad_width(st, wslen);
	while (*wstr && wslen--)
		conversion(st, *(wstr++));
	if (st->flags & WIDTH_F && (st->flags & DASH_F))
		pad_width(st, wslen);
}
