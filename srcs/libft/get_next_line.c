/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:36:28 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 19:10:40 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static t_gnl	*new_file(const int fd)
{
	t_gnl *new;

	if ((new = (t_gnl *)ft_memalloc(sizeof(t_gnl))))
	{
		new->fd = fd;
		new->str = NULL;
	}
	return (new);
}

static t_gnl	*get_file(const int fd, t_gnl **head)
{
	t_gnl *lst;

	if (!(*head))
		return (*head = new_file(fd));
	lst = *head;
	while (lst->next && lst->fd != fd)
		lst = lst->next;
	return ((lst->fd == fd) ? lst : (lst->next = new_file(fd)));
}

static int		str_divide(char **str, char **line)
{
	char	*new;
	char	*div;

	if (!(*line = ft_strsubchr(*str, '\n')))
		return (-1);
	div = ft_strchrs(*str, '\n');
	div++;
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*head = NULL;
	t_gnl			*f;
	char			buff[BUFF_SIZE + 1];
	ssize_t			size;
	char			*tmp;

	if (fd < 0 || !line || read(fd, buff, 0) < 0 || !(f = get_file(fd, &head)))
		return (-1);
	while (!ft_strchrs(f->str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*line = f->str))
				return (0);
			f->str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = f->str;
		f->str = ft_strjoin(f->str, buff);
		free(tmp);
		if (!f->str)
			return (-1);
	}
	return (str_divide(&(f->str), line));
}
