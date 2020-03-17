/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 08:05:36 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/28 08:05:37 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				conv_binary(t_var *st, unsigned char *b, unsigned char j)
{
	char			str_tmp[9];
	char			res[65];
	unsigned char	i;
	unsigned char	k;

	k = 0;
	ft_bzero(res, 65);
	ft_bzero(str_tmp, 9);
	while (k < j)
	{
		i = 0;
		while (i < 8)
		{
			if ((b[j - k - 1] >> i) & 0b00000001)
				str_tmp[7 - i] = '1';
			else
				str_tmp[7 - i] = '0';
			i++;
		}
		ft_strcpy(&res[k * i], str_tmp);
		k++;
	}
	buff(st, ft_strchr(res, '1'), k * i);
}

void				print_binary(t_var *st)
{
	intmax_t		nbr;
	unsigned char	byte[8];
	unsigned char	j;

	j = 0;
	ft_bzero(byte, 8);
	if (!(nbr = va_arg(st->args, intmax_t)))
		return ;
	while (nbr >> j * 8 && j < 8)
	{
		byte[j] = nbr >> j * 8;
		j++;
	}
	conv_binary(st, byte, j);
}
