/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 22:33:54 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/28 19:06:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_strccpy(char **l, t_gnl *gnl, char c, int k)
{
	int				i;
	int				ok;

	i = -1;
	ok = 1;
	(*l)[k] = '\0';
	while (gnl->str[++i] && gnl->str[i] != c)
	{
		if (ok && k > (BUFF_SIZE - 1) * gnl->len)
		{
			if (k > 100000)
				return (-1);
			ok = 0;
			gnl->len++;
			if (!(*l = (char *)ft_realloc(*l, sizeof(char) *
							(((gnl->len) * BUFF_SIZE) + 1))))
				return (-1);
		}
		(*l)[k] = (char)gnl->str[i];
		k++;
	}
	(*l)[k] = '\0';
	return (i);
}

static int				ft_decal_finish(t_gnl *gnl, int i)
{
	int				j;

	if (i == -1)
	{
		if (gnl->str)
			free(gnl->str);
		gnl->str = 0x0;
		return (0);
	}
	j = 0;
	while ((gnl->str)[i])
	{
		(gnl->str)[j] = (gnl->str)[i];
		i++;
		j++;
	}
	j--;
	while (++j < BUFF_SIZE + 1)
		(gnl->str)[j] = '\0';
	return (1);
}

static t_gnl			*ft_new_gnl(int fd, char **l, t_gnl *gnl, t_gnl *prec)
{
	int				len;

	if (gnl != 0x0)
		while ((gnl != 0x0 && gnl->fd != fd) && (prec = gnl) != 0x0)
			gnl = gnl->next;
	len = (gnl && gnl->fd == fd) ? gnl->len : 1;
	if (!(*l = (char *)malloc(sizeof(char) * ((len * BUFF_SIZE) + 1))))
		return (0x0);
	ft_bzero(*l, BUFF_SIZE + 1);
	if (gnl && gnl->fd == fd)
		return (gnl);
	if (!(gnl = (t_gnl *)malloc(sizeof(t_gnl))))
		return (0x0);
	gnl->fd = fd;
	gnl->len = 1;
	gnl->empty = 1;
	if (!(gnl->str = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0x0);
	ft_bzero(gnl->str, BUFF_SIZE + 1);
	gnl->next = 0x0;
	gnl->prec = prec;
	if (prec)
		prec->next = gnl;
	return (gnl);
}

static int				ft_gnl_suite(char **l, t_gnl *gnl, int i, int j)
{
	int				vide;
	int				n;

	vide = (i == 0) ? -1 : 0;
	while (gnl->empty)
	{
		j = 0;
		if ((n = read(gnl->fd, gnl->str, BUFF_SIZE)))
			vide++;
		else
			gnl->empty = 0;
		gnl->str[n] = '\0';
		j = ft_strccpy(l, gnl, '\n', i);
		if (j == -1)
			return (-1);
		i += j;
		if (gnl->str[j] == '\n')
			return (ft_decal_finish(gnl, j + 1));
		if (j == n)
			ft_bzero(gnl->str, BUFF_SIZE);
	}
	if (gnl->empty == 0 && vide == -1)
		return (ft_decal_finish(gnl, -1));
	return (1);
}

int						get_next_line(const int fd, char **l)
{
	static t_gnl	*gnl = 0x0;
	int				i;

	i = -1;
	if (l == 0x0 || fd < 0 || read(fd, 0x0, 0))
		return (-1);
	if (gnl != 0x0)
		while (gnl->prec)
			gnl = gnl->prec;
	gnl = ft_new_gnl(fd, l, gnl, 0x0);
	if (!gnl->str)
		return (0);
	while (gnl->str[++i] && gnl->str[i] != '\n')
		(*l)[i] = gnl->str[i];
	(*l)[i] = '\0';
	if (gnl->empty == 0 && i == 0)
		return (ft_decal_finish(gnl, -1));
	if (gnl->str[i] == '\n' || (gnl->empty == 0 && gnl->str[i] == '\0'))
		return (ft_decal_finish(gnl, i + 1));
	return (ft_gnl_suite(l, gnl, i, 0));
}
