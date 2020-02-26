/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSpecifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:44:47 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/17 14:44:48 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			init_jump_table(t_jumptable *j_table)
{
	j_table['%'] = &putPrecent;
	j_table['c'] = &printChar;
	j_table['C'] = &printChar;
	j_table['s'] = &printStr;
	j_table['S'] = &printStr;
	j_table['p'] = &printHex;
	j_table['i'] = &printInt;
	j_table['d'] = &printInt;
	j_table['u'] = &printUnsignedInt;
	j_table['o'] = &printOct;
	j_table['x'] = &printHex;
	j_table['X'] = &printHex;
	j_table['f'] = &printDouble;
	j_table['F'] = &printDouble;
}

t_jumptable			getHandlerFunct(char c)
{
	static t_jumptable	specifier_jt[128] = {NULL};

	if (specifier_jt['%'] == NULL)
		init_jump_table(specifier_jt);
	if (ft_isascii((int)c))
		return (specifier_jt[(int)c]);
	else
		return (NULL);
}
