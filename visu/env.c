/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:50:19 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/13 18:17:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../visu/visu.h"

void		free_strtab(char ***tab)
{
	char **tmp;

	if (!*tab)
		return ;
	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_strdel(tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}

void		del_anthill(t_list *l)
{
	t_list *tmp;

	while (l)
	{
		tmp = l;
		ft_memdel((void **)tmp);
		l = l->next;
	}

}

void		del_rooms(VISU *v, t_room **room)
{
	t_room *tmp;
	int		i;

	i = 0;
	tmp = *room;
	while ((unsigned int)i < v->graphe->nb_rooms && tmp[i].name)
	{
		ft_strdel(&tmp[i].name);
		ft_memdel((void **)&tmp[i]);
		++i;
	}
	ft_memdel((void **)room);

}


void		free_inttab(int ***tab, int size)
{
	int **tmp;
	int i;

	i = -1;
	if (!*tab)
		return ;
	tmp = *tab;
	while (++i < size)
	{
		ft_memdel((void **)tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}


void		free_env(VISU *v)
{
	del_rooms(v, &v->ins->room);
	free_graphe(v->graphe);
	free_inttab(&v->ins->commands, v->ins->nb_commands);	
	ft_memdel((void **)&v->ins);
	del_anthill(v->anthill);
}

static void		ft_init_uinput(VISU *v)
{
	ft_44minit(&v->uinput.event_m, 1);
	v->uinput.rotx = 0;
	v->uinput.roty = 0;
	v->uinput.zoom = 1;
	v->uinput.mv_hor = 0;
	v->uinput.mv_ver = 0;
	v->uinput.invert = 1;
	v->uinput.height = 0;
	v->uinput.rotcolor = 0;
	v->uinput.color = 0;
	v->uinput.color_map = 0;
}
static void		ft_init_coord(VISU *v)
{
	v->coord.x0 = 0;
	v->coord.x1 = 0;
	v->coord.y0 = 0;
	v->coord.y1 = 0;
	v->setextremes = 0;
}

int		set_env(VISU *v)
{
	ft_bzero(v, sizeof(*v));
	if (!(v->ins = (t_input *)ft_memalloc(sizeof(t_input))))
		return (ERR_ALLOC);
	if (!(v->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
		return (ERR_ALLOC);
	ft_init_uinput(v);
	ft_init_coord(v);
	v->win_w = 1000;
	v->win_h = 1000;
	v->graphe->start = -1;
	v->graphe->end = -1;
	v->mesh_init = 40;
	v->ppmove = 20;
	v->pause = 0;
	v->speed = 1;
	ft_4vinit(&v->shift, 0, 0, 0);
	return (1);
}
