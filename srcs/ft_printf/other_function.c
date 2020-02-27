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

void		freeBuffer(s_fwpls *st)
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
				freeBuffer(st);
		}
}

void		pad(s_fwpls *st, int padLen, char padChar)
{
	char 	*padStr;

	if (padLen > 0)
	{
		if ((padStr = ft_strnew(padLen)))
		{
			ft_memset(padStr, padChar, (size_t)padLen);
			buff(st, padStr, padLen);
			free(padStr);
		}
	}
}

void		padWidth(s_fwpls *st, int argWidth)
{
	int 	padWidth;

	padWidth = st->width - argWidth;
	pad(st, padWidth, ' ');
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