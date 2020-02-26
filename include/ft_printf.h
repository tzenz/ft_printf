/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:47:58 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/04 18:47:59 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>

# define HASH_FLAG		1 // #
# define ZERO_FLAG		2 // 0
# define DASH_FLAG		4 // -
# define PLUS_FLAG		8 // +
# define SPACE_FLAG		16 // ' '
# define APOST_FLAG		32 // '''
# define CONV_DOUBLE	64 //
# define H_FLAG			128 // h
# define HH_FLAG		256 // hh
# define L_FLAG			512 // l
# define LL_FLAG		1024 // ll
# define J_FLAG			2048 // j
# define Z_FLAG			4096 // z
# define T_FLAG			8192 // t
# define FLOAT_L_FLAG	16384 // L
# define WIDTH_FLAG		32768 // ширина
# define PRECI_FLAG		65536 // точность
# define LEN_OB_FLAG	131072 // int and long...
# define FMT_INVALID	262144

# define BUF_SIZE 4096
# define ULL unsigned long long
# define MOD(a) (((a) > 0) ? (a) : -(a))
#define UPP(x) ((x)=='X'||(x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')

void				ft_putbyte(int x);
uintmax_t			ft_power(uintmax_t base, uintmax_t power);

typedef struct		s_fwpls
{
	int 			fd;
	int 			flags;
	int				width;
	int				precision;
	char 			*length;
	char 			specifier;
	char 			buff[BUF_SIZE];
	size_t 			lenBuff;
	size_t 			len;
	const char		*fmt;
	const char 		*strt;
	va_list 		args;
	int 			base;
	int 			sign;
	uintmax_t 		hex;
}					s_fwpls;

union				u_union
{
	ULL				l;
	double			d;
}					u;

typedef void		(*t_jumptable)(s_fwpls *st);

int 				ft_printf(char *format,...);
void				parseFlags(s_fwpls *st);
void				parseWidth(s_fwpls *st);
void				parsePrecision(s_fwpls *st, int recurseLevel);
void				parseLenght(s_fwpls *st);

t_jumptable			getHandlerFunct(char c);

void				putPrecent(s_fwpls *st);

void				flushBuffer(s_fwpls *st);
void				buff(s_fwpls *st, const void *s, size_t nbyte);
void				padWidth(s_fwpls *st, int arg_width);
void				resetPrintf(s_fwpls *st);

intmax_t			nbrLen(s_fwpls *st, intmax_t n);
void				intPadWidth(s_fwpls *st, int totalLen, int printPL_SP);
void				pad(s_fwpls *st, int pad_len, char pad_char);
void				padFlags(s_fwpls *st, int printPL_SP);
void				itoaBase(s_fwpls *st, uintmax_t nbr, int len);

void				conversion(s_fwpls *st, int wc);
size_t				wStrLen(wchar_t *wstr);
void				printWChar(s_fwpls *st);
void				printWStr(s_fwpls *st);
void				printChar(s_fwpls *st);
void				printStr(s_fwpls *st);

void				printInt(s_fwpls *st);
void				printUnsignedInt(s_fwpls *st);
void				printOct(s_fwpls *st);
void				printHex(s_fwpls *st);

void				printDouble(s_fwpls *st);
void				convertDouble(s_fwpls *st, long double nbr, size_t intLen, size_t totalLen);

#endif
