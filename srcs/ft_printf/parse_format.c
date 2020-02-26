/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseFlags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:09:28 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/14 20:09:28 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define IS_FLAG(x) ((x)=='#'||(x)=='0'||(x)=='-'||(x)=='+'||(x)==' '||(x)=='\'')
#define IS_LEN(y) ((y)=='h'||(y)=='l'||(y)=='j'||(y)=='z'||(y)=='t'||(y)=='L')
#define IS_SLEN(z) ((z)=='j'||(z)=='z'||(z)=='t'||(z)=='L')

void		parseFlags(s_fwpls *st)
{
	if (IS_FLAG(*st->fmt))
	{
		if (*st->fmt == '#')
			st->flags |= HASH_FLAG;
		else if (*st->fmt == '0')
			st->flags |= ZERO_FLAG;
		else if (*st->fmt == '-')
			st->flags |= DASH_FLAG;
		else if (*st->fmt == '+')
			st->flags |= PLUS_FLAG;
		else if (*st->fmt == ' ')
			st->flags |= SPACE_FLAG;
		else if (*st->fmt == '\'')
			st->flags |= APOST_FLAG;
		st->fmt++;
		parseFlags(st);
	}
}

void		parseWidth(s_fwpls *st) //в ориг pritf width * = -10, '-' считается флагом
{
	int		tentativeWight;

	if (!(st->flags & FMT_INVALID) && (*st->fmt == '*' || ft_isdigit(*st->fmt)))
	{
		if (!(st->flags & FMT_INVALID) && *st->fmt == '*')
		{
			st->fmt++;
			tentativeWight = va_arg(st->args, int);
			st->flags |= (tentativeWight < 0) ? DASH_FLAG : 0;
			st->width = MOD(tentativeWight);
			st->flags |= WIDTH_FLAG;
		}
		if (!(st->flags & FMT_INVALID) && ft_isdigit(*st->fmt))
		{
			st->flags |= (st->flags & WIDTH_FLAG) ? FMT_INVALID : 0;
			while (!(st->flags & FMT_INVALID) && ft_isdigit(*st->fmt))
				st->width = st->width * 10 + (*(st->fmt++) - '0');
			st->flags |= WIDTH_FLAG;
		}
		parseWidth(st);
	}
}

void		parsePrecision(s_fwpls *st, int recurseLevel)
{
	if (!(st->flags & FMT_INVALID) && (*st->fmt == '.' || recurseLevel > 0))
	{
		st->fmt = (*st->fmt == '.') ? st->fmt + 1 : st->fmt;
		if (*st->fmt == '*' || ft_isdigit(*st->fmt))
		{
			st->flags |= (st->flags & PRECI_FLAG) ? FMT_INVALID : 0;
			if (!(st->flags & FMT_INVALID) && *st->fmt == '*')
			{
				st->fmt++;
				st->precision = va_arg(st->args, int);
				st->flags |= PRECI_FLAG;
			}
			if (!(st->flags & FMT_INVALID) && ft_isdigit(*st->fmt))
			{
				st->flags |= (st->flags & PRECI_FLAG) ? FMT_INVALID : 0;
				while (!(st->flags & FMT_INVALID) && ft_isdigit(*st->fmt))
					st->precision = st->precision * 10 + (*(st->fmt++) - '0');
				st->flags |= PRECI_FLAG;
			}
			parsePrecision(st, recurseLevel + 1);
		}
		st->flags |= PRECI_FLAG;
	}
}

void		parseLongLenght(s_fwpls *st, char c, int sFlag, int dFlag)
{
	if (*st->fmt == c)
	{
		if (st->flags & LEN_OB_FLAG)
		{
			if ((st->flags & sFlag) && !(st->flags & dFlag))
			{
				st->flags ^= sFlag;
				st->flags |= dFlag;
			}
			else
				st->flags |= FMT_INVALID;
		}
		else
		{
			st->flags |= sFlag;
			st->flags |= LEN_OB_FLAG;
		}
	}
}

void		parseLenght(s_fwpls *st)
{
	if (!(st->flags & FMT_INVALID) && IS_LEN(*st->fmt))
	{
		parseLongLenght(st, 'h', H_FLAG, HH_FLAG);
		parseLongLenght(st, 'l', L_FLAG, LL_FLAG);
		if (IS_SLEN(*st->fmt))
		{
			if (!(st->flags & LEN_OB_FLAG))
			{
				st->flags |= (*st->fmt == 'j') ? J_FLAG : 0;
				st->flags |= (*st->fmt == 'z') ? Z_FLAG : 0;
				st->flags |= (*st->fmt == 't') ? T_FLAG : 0;
				st->flags |= (*st->fmt == 'L') ? FLOAT_L_FLAG : 0;
				st->flags |= LEN_OB_FLAG;
			}
			else
				st->flags |= FMT_INVALID;
		}
		st->fmt++;
		parseLenght(st);
	}
	else if (*st->fmt == '.') // ?????????? точка после длинны, по разному реагирует
		st->flags |= FMT_INVALID;
}