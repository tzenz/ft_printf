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

void		print_char(t_var *st)
{
	char	c;

	if (st->flags & L_FLAG || st->specifier == 'C')
		print_wchar(st);
	else
	{
		c = (char)va_arg(st->args, int);
		if (st->flags & WIDTH_F && !(st->flags & DASH_F))
			pad(st, st->width - 1, (st->flags & ZERO_F) ? '0' : ' ');
		buff(st, &c, 1);
		if (st->flags & WIDTH_F && st->flags & DASH_F)
			pad_width(st, 1);
	}
}

void		print_str(t_var *st)
{
	char	*str;
	int		s_len;

	if (st->flags & L_FLAG || st->specifier == 'S')
		print_wstr(st);
	else
	{
		if ((str = (char *)va_arg(st->args, char *)) == NULL)
			str = "(null)";
		s_len = ft_strlen(str);
		if (st->precision < 0)
			st->precision = s_len;
		st->precision = (st->precision > s_len) ? s_len : st->precision;
		s_len = (st->flags & PRECI_F) ? st->precision : s_len;
		if (st->flags & WIDTH_F && !(st->flags & DASH_F))
			pad(st, st->width - s_len, (st->flags & ZERO_F) ? '0' : ' ');
		buff(st, str, s_len);
		if (st->flags & WIDTH_F && (st->flags & DASH_F))
			pad_width(st, s_len);
	}
}

void		print_percent(t_var *st)
{
	if (st->flags & WIDTH_F && !(st->flags & DASH_F))
		nbr_pad_width(st, 1, 1);
	buff(st, "%", 1);
	if (st->flags & WIDTH_F && (st->flags & DASH_F))
		pad_width(st, 1);
}
