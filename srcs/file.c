/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:41:53 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/16 18:42:48 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
int				addfile(t_file *file, int value);
int				removefile(t_file *file);
t_file			*new_file(t_graphe *g);
t_file			*clean_file(t_file *file, int size);

t_file			*new_file(t_graphe *g)
{
	t_file *file;

	file = 0x0;
	if (!(file = (t_file*)malloc(sizeof(t_file))) || !g || g->nb_rooms == 0)
		exit(3);
	file->begin = 0;
	file->end = 0;
	if(!(file->tab = (int *)ft_memalloc(sizeof(int) * g->nb_rooms)))
		exit(3);
	return (file);
}

t_file			*clean_file(t_file *file, int size)
{
	if (!file)
		return (0x0);
	ft_bzero(file->tab, size * sizeof(int));
	file->begin = 0;
	file->end = 0;
	return (file);
}

int				removefile(t_file *file)
{
	if (!file)
	{
		ft_putstr("GROS PB impossible file null removefile\n");
		exit(4);
	}
	if (file->begin >= file->end)
		return (-1);
	file->begin += 1;
	return (file->tab[file->begin - 1]);
}

int				addfile(t_file *file, int value)
{
	if (!file)
	{
		ft_putstr("GROS PB impossible file null addfile\n");
		exit(4);
	}
	file->tab[file->end] = value;
	file->end += 1;
	return (1);
}

int				isemptyfile(t_file *file)
{
	if (!file)
	{
		ft_putstr("GROS PB impossible file null addfile\n");
		exit(4);
	}
	if (file->begin >= file->end)
		return (1);
	else
		return (0);
}
