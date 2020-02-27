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
#include "float.h"
#include <limits.h>

void			parseFormat(s_fwpls *st)
{
	t_jumptable		handlerFunct;
	const char 		*fmtStart;

	fmtStart = st->fmt;
	if (st->fmt++)
	{
		st->strt = st->fmt;
		parseFlags(st);
		parseWidth(st);
		parsePrecision(st, 0);
		parseLenght(st);
		st->specifier = *st->fmt;
		if ((handlerFunct = getHandlerFunct(st->specifier)) == NULL)
			st->flags |= FLG_INVALID;
		else if (!(st->flags & FLG_INVALID))
		{
			handlerFunct(st);
			st->fmt++;
		}
	}
	st->strt = (st->flags & FLG_INVALID) ? fmtStart : st->fmt; //если флаг не валидный, выведи как строку
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
			buff(&st, st.strt, st.fmt - st.strt); //запиши в буфер все что перед '%'
			parseFormat(&st);
			resetPrintf(&st);
		}
	}
	buff(&st, st.strt, st.fmt - st.strt);
	freeBuffer(&st); //если строка законилась выведи буфер
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
	ft_printf("%Lf\n", -56.2012685l);
//	ft_printf("%.19f", 1.025978548534310421934);
//	ft_printf("%lc", 128005);
//	printf("%lu", ~0UL);
//	ft_putbyte(0, ~0UL);
	return (0);
}