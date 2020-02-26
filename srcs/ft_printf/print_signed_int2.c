/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_int2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:41:54 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/19 18:41:55 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p'||(x)=='a'||(x)=='A')
# define FMOD(a) (((a) < 0.0f) ? (-a) : (a))
# define ULLMAX	(~0UL)
# define LLMAX_MIN ((long long)1 << 63)

void		padFlags(s_fwpls *st, int printPL_SP)
{
	if (st->sign)
		buff(st, "-", 1);
	else if (st->flags & PLUS_FLAG && printPL_SP && st->specifier != 'u') //для unsigned int знак не вывыодится
		buff(st, "+", 1);
	else if (st->flags & SPACE_FLAG && printPL_SP && st->specifier != 'u') //для unsigned int space не выводится
		buff(st, " ", 1);
	if ((st->flags & HASH_FLAG && HEX(st->specifier) && st->hex != 0) || st->specifier == 'p')
		buff(st, UPP(st->specifier) ? "0X" : "0x", 2);
}

void			itoaBase(s_fwpls *st, uintmax_t nbr, int len)
{
	uintmax_t			tmp;
	int 				tmpLen;
	char				str[27];
	char 				c;
	int 				prec;

	if (nbr == LLMAX_MIN)
	{
        buff(st, "9223372036854775808", 19);
        return;
    }
    tmp = nbr;
    tmpLen = len;
    str[len] = '\0';
    prec = st->precision;
    c = (UPP(st->specifier)) ? 'A' : 'a';
	while (tmpLen-- > 0)
	{
		if (st->flags & CONV_DOUBLE && prec-- == 0)
			break;
		str[tmpLen] = (tmp % st->base < 10) ? tmp % st->base + '0' : tmp % st->base + c - 10;
		tmp /= st->base;
	}
	buff(st, str, len);
}

long double		power(int base, int pwr, long double nbr)
{
	uintmax_t	res;

	res = 1;

	if (base == 0)
		return (1);
	while (pwr--)
		res *= base;
	return (((nbr + (uintmax_t)nbr) - (uintmax_t)nbr) * res);
}

long double		powerLong(int base, int pwr, long double nbr)
{
	uintmax_t	res;

	res = 1;
	while (pwr > 19)
	{
		res *= base;
		pwr--;
	}
	return (power(base, pwr, (nbr - (uintmax_t)nbr) * res));
}

long double		roundFrac(s_fwpls *st, long double frac)
{
	if (frac > ULLMAX)
		return ((uintmax_t)FMOD(frac / 100) % st->base >= (uintmax_t)(st->base / 2))
			   ? (frac / st->base) + 1 : frac / st->base;
	else
	{
		printf("%Lf\n", frac);
		printf("%lu\n", ((uintmax_t) FMOD(frac) % st->base));
		return ((uintmax_t) FMOD(frac) % st->base >= (uintmax_t) (st->base / 2))
			   ? (frac / st->base) + 1 : frac / st->base;
	}
}

void			convertDouble(s_fwpls *st, long double nbr, size_t intLen)
{
	long double	frac;

	if ((MOD(nbr) - (uintmax_t)MOD(nbr)) > 0.5 && st->precision == 0)
		itoaBase(st, (uintmax_t)MOD(nbr) + 1, intLen);
	else
		itoaBase(st, (uintmax_t)MOD(nbr), intLen);
	st->flags |= CONV_DOUBLE;
	if (st->precision >= 19)
		frac = powerLong(st->base, st->precision + 1, FMOD(nbr));
	else
		frac = power(st->base, st->precision + 1, FMOD(nbr));
	frac = roundFrac(st, frac);
	if (st->precision == 6 && (uintmax_t)frac / 1000000 > (uintmax_t)MOD(nbr))
	{
		st->buff[st->len - 1]++;
		buff(st, ".", 1);
		itoaBase(st, (uintmax_t)FMOD(frac), st->precision);
	}
	else if (st->precision != 0)
	{
		buff(st, ".", 1);
		itoaBase(st, (uintmax_t)FMOD(frac), st->precision);
	}
	if (st->precision == 0 && st->flags & HASH_FLAG)
		buff(st, ".", 1);
}
