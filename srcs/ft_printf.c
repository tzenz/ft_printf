/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:24:17 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/14 13:24:18 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			parse_format(t_var *st)
{
	t_jumptable		handler_funct;
	const char		*fmt_start;

	fmt_start = st->fmt;
	if (st->fmt++)
	{
		st->strt = st->fmt;
		parse_flags(st);
		parse_width(st);
		parse_precision(st, 0);
		parse_lenght(st);
		st->specifier = *st->fmt;
		if ((handler_funct = get_handler_funct(st)) == NULL)
			st->flags |= FLG_INVALID;
		else if (!(st->flags & FLG_INVALID))
		{
			handler_funct(st);
			st->fmt++;
		}
	}
	if (st->flags & FLG_INVALID && st->flags & WIDTH_F && st->flags & PRECI_F)
		st->strt = fmt_start;
	else
		st->strt = st->fmt;
}

int				ft_vfprintf(int fd, const char *format, va_list args)
{
	t_var		st;

	reset_printf(&st);
	st.len_buff = 0;
	st.len = 0;
	st.fd = fd;
	va_copy(st.args, args);
	st.fmt = format;
	st.strt = st.fmt;
	while (*st.fmt)
	{
		if (*st.fmt != '%')
			st.fmt++;
		else
		{
			buff(&st, st.strt, st.fmt - st.strt);
			parse_format(&st);
			reset_printf(&st);
		}
	}
	buff(&st, st.strt, st.fmt - st.strt);
	free_buffer(&st);
	va_end(st.args);
	return (st.len);
}

int				ft_printf(char *format, ...)
{
	va_list		args;
	int			len;

	len = 0;
	if (format)
	{
		va_start(args, format);
		len = ft_vfprintf(1, format, args);
		va_end(args);
	}
	return (len);
}
