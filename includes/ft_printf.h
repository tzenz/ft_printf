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
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

# define HASH_F			1
# define ZERO_F			2
# define DASH_F			4
# define PLUS_F			8
# define SPACE_F		16
# define CONV_DOUBLE	64
# define H_FLAG			128
# define HH_FLAG		256
# define L_FLAG			512
# define LL_FLAG		1024
# define J_FLAG			2048
# define Z_FLAG			4096
# define FLOAT_L_FLAG	16384
# define WIDTH_F		32768
# define PRECI_F		65536
# define LEN_F			131072
# define FLG_INVALID	262144

# define BUF_SIZE		4096

# define BLUE			"\e[00;34m"
# define YELLOW			"\e[01;33m"
# define GREEN			"\e[00;32m"
# define RED			"\e[00;31m"
# define END			"\e[m"

typedef struct			s_var
{
	int					fd;
	int					flags;
	int					width;
	int					precision;
	char				specifier;
	char				buff[BUF_SIZE];
	size_t				len_buff;
	size_t				len;
	const char			*fmt;
	const char			*strt;
	va_list				args;
	int					base;
	int					sign;
	uintmax_t			hex;
}						t_var;

union					u_union
{
	unsigned long long	l;
	double				d;
}						u;

typedef void			(*t_jumptable)(t_var *st);

int						ft_printf(char *format, ...);
void					parse_flags(t_var *st);
void					parse_width(t_var *st);
void					parse_precision(t_var *st, int recurse_level);
void					parse_lenght(t_var *st);
t_jumptable				get_handler_funct(t_var *st);
void					print_percent(t_var *st);
void					free_buffer(t_var *st);
void					buff(t_var *st, const void *s, size_t nbyte);
void					pad_width(t_var *st, int arg_width);
void					reset_printf(t_var *st);
int						nbr_len(t_var *st, intmax_t n);
int						unbr_len(t_var *st, uintmax_t n);
void					nbr_pad_width(t_var *st, int len, int print_pl_sp);
void					pad(t_var *st, int pad_len, char pad_char);
void					pad_flags(t_var *st, int print_pl_sp);
void					itoa_base(t_var *st, uintmax_t nbr, int len);
void					conversion(t_var *st, int wc);
size_t					w_strlen(wchar_t *wstr);
void					print_wchar(t_var *st);
void					print_wstr(t_var *st);
void					print_char(t_var *st);
void					print_str(t_var *st);
void					print_int(t_var *st);
void					print_uint(t_var *st);
void					print_oct(t_var *st);
void					print_hex(t_var *st);
void					print_double(t_var *st);
void					convert_dbl(t_var *st, long double nbr, size_t int_len);
void					print_binary(t_var *st);
intmax_t				int_args(t_var *st);
uintmax_t				u_int_args(t_var *st);
long double				power(int base, int pwr, long double nbr);
long double				power_l(int base, int pwr, long double nbr);

int						hex(char c);
int						upp(char c);
long double				f_mod(long double a);
long double				mod(long double i);
intmax_t				max(intmax_t a, intmax_t b);

#endif
