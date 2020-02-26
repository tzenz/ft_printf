/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_precent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:42:40 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/19 15:42:41 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		putPrecent(s_fwpls *st)
{
	if (st->flags & WIDTH_FLAG && !(st->flags & DASH_FLAG))
		intPadWidth(st, 1, 1);
	buff(st, "%", 1);
	if (st->flags & WIDTH_FLAG && (st->flags & DASH_FLAG))
		padWidth(st, 1);
}