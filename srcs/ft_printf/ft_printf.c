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
#include <math.h>
#include <limits.h>

void			parseFormat(s_fwpls *st)
{
	t_jumptable		handler_funct;
	const char 		*fmt_start;

	fmt_start = st->fmt;
	if (st->fmt++ != '\0')
	{
		st->strt = st->fmt;
		parseFlags(st);
		parseWidth(st);
		parsePrecision(st, 0);
		parseLenght(st);
		st->specifier = *st->fmt;
		if ((handler_funct = getHandlerFunct(st->specifier)) == NULL)
			st->flags |= FMT_INVALID;
		else if (!(st->flags & FMT_INVALID))
		{
			handler_funct(st);
			st->fmt++;
		}
	}
	st->strt = (st->flags & FMT_INVALID) ? fmt_start : st->fmt;
}

int				ft_vfprintf(int fd, const char *format, va_list args)
{
	s_fwpls		st;

	ft_bzero(&st, sizeof(st));
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
			parseFormat(&st);
			resetPrintf(&st);
		}
	}
	buff(&st, st.strt, st.fmt - st.strt);
	flushBuffer(&st);
	va_end(st.args);
	return (st.len);
}
int 			ft_printf(char *format,...)
{
	va_list		args;
	int 		len;

	len = 0;
	if (format)
	{
		va_start(args, format);
		len = ft_vfprintf(1, format, args);
		va_end(args);
	}
	return (len);
}

int 	main()
{
//	ft_printf("%f", -56.2012685);
	ft_printf("%.19f", 1.025978548534310421934);
//	ft_printf("this %f float", 1.5);
//	printf("%lu", ~0UL);
//	printf("%lu", sizeof(unsigned long));
//	ft_putbyte(0, ~0UL);
	return (0);
}