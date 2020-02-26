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

int			wCharlen(int wc)
{
	if (wc <= 0x7f)			//127
		return (1);
	else if (wc <= 0x07FF)	//2047
		return (2);
	else if (wc <= 0xFFFF)	//65535
		return (3);
	else if (wc <= 0x10FFFF)	//1114111
		return (4);
	return (0);
}

//size_t		wStrLen(wchar_t *wstr)
//{
//	size_t	wlen;
//
//	wlen = 0;
//	while (*wstr != L'\0')
//	{
//		wlen += wCharlen(*wstr);
//		wstr++;
//	}
//	return (wlen);
//}

size_t		wStrLen(wchar_t *wstr)
{
	size_t	wCharLen;

	wCharLen = 0;
	while (*(wstr++) != L'\0')
		wCharLen++;
	return (wCharLen);
}
