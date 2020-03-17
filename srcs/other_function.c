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

void		free_buffer(t_var *st)
{
	write(st->fd, st->buff, st->len_buff);
	st->len_buff = 0;
}

void		buff(t_var *st, const void *s, size_t nbyte)
{
	char	*str;

	str = (char *)s;
	if (nbyte + st->len_buff < BUF_SIZE)
		while (nbyte--)
		{
			st->buff[st->len_buff++] = *str++;
			st->len++;
		}
	else
		while (nbyte)
		{
			while (st->len_buff < BUF_SIZE && nbyte)
			{
				st->buff[st->len_buff++] = *str++;
				st->len++;
				nbyte--;
			}
			if ((BUF_SIZE - st->len_buff) < 1)
				free_buffer(st);
		}
}

void		pad(t_var *st, int pad_len, char pad_char)
{
	char	pad_str[pad_len];

	if (pad_len > 0)
	{
		ft_memset(pad_str, pad_char, (size_t)pad_len);
		buff(st, pad_str, pad_len);
	}
}

void		pad_width(t_var *st, int arg_width)
{
	int		pad_width;

	pad_width = st->width - arg_width;
	pad(st, pad_width, ' ');
}

void		reset_printf(t_var *st)
{
	st->flags = 0;
	st->width = 0;
	st->precision = 0;
	st->base = 0;
	st->sign = 0;
	st->hex = 0;
	st->sign = 0;
	st->specifier = '\0';
}
