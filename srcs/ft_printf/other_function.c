/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:17:17 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/17 15:17:18 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flushBuffer(s_fwpls *st)
{
	write(st->fd, st->buff, st->lenBuff);
	st->lenBuff = 0;
}

void		buff(s_fwpls *st, const void *s, size_t nbyte)
{
	char 	*str;

	str = (char *)s;
	if (nbyte + st->lenBuff < BUF_SIZE)
		while (nbyte--)
		{
			st->buff[st->lenBuff++] = *str++;
			st->len++;
		}
	else
		while (nbyte)
		{
			while (st->lenBuff < BUF_SIZE && nbyte)
			{
				st->buff[st->lenBuff++] = *str++;
				st->len++;
                nbyte--;
			}
			if ((BUF_SIZE - st->lenBuff) < 1)
				flushBuffer(st);
		}
}

void		pad(s_fwpls *st, int pad_len, char pad_char)
{
	char 	*pad_str;

	pad_str = NULL;
	if (pad_len > 0)
	{
		if ((pad_str = ft_strnew(pad_len)))
		{
			ft_memset(pad_str, pad_char, (size_t)pad_len);
			buff(st, pad_str, pad_len);
			free(pad_str);
		}
	}
}

void		padWidth(s_fwpls *st, int arg_width)
{
	int 	final_pad_width;

	final_pad_width = st->width - arg_width;
	pad(st, final_pad_width, ' ');
}

void		resetPrintf(s_fwpls *st)
{
	st->flags = 0;
	st->width = 0;
	st->precision = 0;
	st->base = 0;
	st->sign = 0;
	st->hex = 0;
	st->specifier = '\0';
}