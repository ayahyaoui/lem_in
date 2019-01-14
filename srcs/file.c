/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:41:53 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/14 20:23:35 by anyahyao         ###   ########.fr       */
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
		return (0x0);
	file->begin = 0;
	file->end = 0;
	if(!(file->tab = (int *)ft_memalloc(sizeof(int) * g->nb_rooms)))
		return (0x0);
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
		return (-1);
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
		return (-1);
	}
	file->tab[file->end] = value;
	file->end += 1;
	return (1);
}

int				isemptyfile(t_file *file)
{
	if (!file)
	{
		ft_putstr("GROS PB impossible file null isemptyfile\n");
		return (-1);
	}
	if (file->begin >= file->end)
		return (1);
	else
		return (0);
}

void	printfile(t_file *f)
{
	int i;
	if (!f)
	{
		ft_putstr("GROS PB impossible file null printfile\n");
	}
	i = f->begin - 1;
	ft_printf("file %d-%d:", f->begin, f->end);
	while (++i < f->end - 1)
		ft_printf("%d ->", f->tab[i]);
	if (i < f->end)
		ft_printf("%d\n", f->tab[i]);
}
