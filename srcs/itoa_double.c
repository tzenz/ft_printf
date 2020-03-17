/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_int2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:41:54 by kkatelyn          #+#    #+#             */
/*   Updated: 2020/02/19 18:41:55 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			itoa_base(t_var *st, uintmax_t nbr, int len)
{
	char		str[50];
	int			prec;
	int			tmp_len;
	char		c;

	str[len] = '\0';
	if ((intmax_t)nbr == ((long long)1 << 63) && st->base == 10)
	{
		buff(st, "9223372036854775808", 19);
		return ;
	}
	prec = st->precision;
	c = (upp(st->specifier)) ? 'A' : 'a';
	tmp_len = len;
	while (tmp_len-- > 0)
	{
		if (st->flags & CONV_DOUBLE && prec-- == 0)
			break ;
		str[tmp_len] = (nbr % st->base < 10) ? nbr % st->base + '0'
				: nbr % st->base + c - 10;
		nbr /= st->base;
	}
	buff(st, str, len);
}

long double		rnd_frac(t_var *st, long double frac)
{
	uintmax_t	tmp_u_frac;
	long double	tmp_frac;

	tmp_u_frac = (uintmax_t)frac % st->base;
	tmp_frac = frac - (uintmax_t)frac;
	if (st->flags & FLOAT_L_FLAG && tmp_u_frac < 5)
		return (frac / st->base);
	else if (st->flags & FLOAT_L_FLAG && tmp_u_frac == 5 && tmp_frac == 0.0l)
		return (frac / st->base);
	else if (st->flags & FLOAT_L_FLAG && tmp_u_frac == 5)
		return (tmp_frac >= 0.5) ? (frac / st->base) + 1 : frac / st->base;
	else
		return ((uintmax_t)frac % st->base >= (uintmax_t)(st->base / 2))
			? (frac / st->base) + 1 : frac / st->base;
}

void			convert_dbl(t_var *st, long double nbr, size_t int_len)
{
	long double	frac;

	if ((mod(nbr) - (uintmax_t)mod(nbr)) > 0.5 && st->precision == 0)
		itoa_base(st, (uintmax_t)mod(nbr) + 1, int_len);
	else
		itoa_base(st, (uintmax_t)mod(nbr), int_len);
	st->flags |= CONV_DOUBLE;
	if (st->precision >= 19)
		frac = rnd_frac(st, power_l(st->base, st->precision + 1, f_mod(nbr)));
	else
		frac = rnd_frac(st, power(st->base, st->precision + 1, f_mod(nbr)));
	if (((uintmax_t)frac / ft_pow(st->base, st->precision)) >
		(uintmax_t)mod(nbr) && st->precision != 0)
	{
		st->buff[st->len - 1]++;
		buff(st, ".", 1);
		itoa_base(st, (uintmax_t)f_mod(frac), st->precision);
	}
	else if (st->precision != 0)
	{
		buff(st, ".", 1);
		itoa_base(st, (uintmax_t)f_mod(frac), st->precision);
	}
	if (st->precision == 0 && st->flags & HASH_F)
		buff(st, ".", 1);
}
