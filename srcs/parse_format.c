/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:07:43 by tzenz             #+#    #+#             */
/*   Updated: 2020/03/02 17:07:47 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		parse_flags(t_var *st)
{
	char	c;

	c = *st->fmt;
	if (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ')
	{
		if (c == '#')
			st->flags |= HASH_F;
		else if (c == '0')
			st->flags |= ZERO_F;
		else if (c == '-')
			st->flags |= DASH_F;
		else if (c == '+')
			st->flags |= PLUS_F;
		else if (c == ' ')
			st->flags |= SPACE_F;
		st->fmt++;
		parse_flags(st);
	}
}

void		parse_width(t_var *st)
{
	int		pre_wight;

	if (!(st->flags & FLG_INVALID) && (*st->fmt == '*' || ft_isdigit(*st->fmt)))
	{
		if (!(st->flags & FLG_INVALID) && *st->fmt == '*')
		{
			st->fmt++;
			pre_wight = va_arg(st->args, int);
			st->flags |= (pre_wight < 0) ? DASH_F : 0;
			st->width = mod(pre_wight);
			st->flags |= WIDTH_F;
		}
		if (!(st->flags & FLG_INVALID) && ft_isdigit(*st->fmt))
		{
			st->width = (st->flags & WIDTH_F) ? 0 : st->width;
			while (!(st->flags & FLG_INVALID) && ft_isdigit(*st->fmt))
				st->width = st->width * 10 + (*(st->fmt++) - '0');
			st->flags |= WIDTH_F;
		}
		parse_width(st);
	}
}

void		parse_precision(t_var *st, int recurse_level)
{
	if (!(st->flags & FLG_INVALID) && (*st->fmt == '.' || recurse_level > 0))
	{
		st->fmt = (*st->fmt == '.') ? st->fmt + 1 : st->fmt;
		if (*st->fmt == '*' || ft_isdigit(*st->fmt))
		{
			st->flags |= (st->flags & PRECI_F) ? FLG_INVALID : 0;
			if (!(st->flags & FLG_INVALID) && *st->fmt == '*')
			{
				st->fmt++;
				st->precision = va_arg(st->args, int);
				st->flags |= PRECI_F;
			}
			if (!(st->flags & FLG_INVALID) && ft_isdigit(*st->fmt))
			{
				st->flags |= (st->flags & PRECI_F) ? FLG_INVALID : 0;
				while (!(st->flags & FLG_INVALID) && ft_isdigit(*st->fmt))
					st->precision = st->precision * 10 + (*(st->fmt++) - '0');
				st->flags |= PRECI_F;
			}
			parse_precision(st, recurse_level + 1);
		}
		st->flags |= PRECI_F;
		while (*st->fmt == '.' || ft_isdigit(*st->fmt))
			st->fmt++;
	}
}

void		parse_long_lenght(t_var *st, char h_l, int s_flag, int d_flag)
{
	if (*st->fmt == h_l)
	{
		if (st->flags & LEN_F)
		{
			if ((st->flags & s_flag) && !(st->flags & d_flag))
			{
				st->flags ^= s_flag;
				st->flags |= d_flag;
				st->flags ^= LEN_F;
			}
		}
		else
		{
			st->flags |= s_flag;
			st->flags |= LEN_F;
		}
	}
}

void		parse_lenght(t_var *st)
{
	char	c;

	c = *st->fmt;
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 'L')
	{
		parse_long_lenght(st, 'h', H_FLAG, HH_FLAG);
		parse_long_lenght(st, 'l', L_FLAG, LL_FLAG);
		if (c == 'j' || c == 'z' || c == 'L')
		{
			if (!(st->flags & LEN_F))
			{
				st->flags |= (*st->fmt == 'j') ? J_FLAG : 0;
				st->flags |= (*st->fmt == 'z') ? Z_FLAG : 0;
				st->flags |= (*st->fmt == 'L') ? FLOAT_L_FLAG : 0;
				st->flags |= LEN_F;
			}
		}
		st->fmt++;
		parse_lenght(st);
	}
}
