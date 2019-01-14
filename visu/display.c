/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 19:58:35 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdlib.h>
#include <stdio.h> //

void	display_adj_mtrx(int **tab, int size)
{
	int	i;
	int	j;	

	i = -1;
	ft_printf("\t | ", i);
	while (++i < size)
		ft_printf("%d ", i);
	ft_printf("\n");
	j = -1;
	while (++j < size)
	{
		i = -1;
		ft_printf("%d\t | ", j);
		while (++i < size) 
			ft_printf("%d ", tab[j][i]);
		ft_printf("\n");
	}

}

void		draw_ant_legs(VISU *v, int *ant, int scale, int option)
{
	double x;
	double  y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	y = v->ins->room[ant[CURRENT]].pos.y;
	(void)ant;
	v->coord.x0 = x + (option ? v->delta.x + scale : v->delta.x - scale);
	v->coord.x0 -= 2;
	v->coord.y0 = y + v->delta.y - scale;
	v->coord.x1 = x + (option ? v->delta.x - scale : v->delta.x + scale);
	v->coord.x1 -= 2;
	v->coord.y1 = y + v->delta.y + scale;
	ft_drawline(v);
}

void		display_ant(VISU *v, int *ant, int scale)
{
	double x;
	double  y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	y = v->ins->room[ant[CURRENT]].pos.y;
	if (!ant || ant[CURRENT] == -1)
		return ;
	if (scale < 5)
		scale = 5;
	v->color = COL_ANT;
	display_square(v, ant, -2, COL_ANT);
	v->coord.x0 = x + v->delta.x - 2 * scale + 2;
	v->coord.y0 = y + v->delta.y;
	v->coord.x1 = x + v->delta.x + 4;
	v->coord.y1 = y + v->delta.y;
	ft_drawline(v);
	v->coord.x0 = x + v->delta.x - 2;
	v->coord.y0 = y + v->delta.y - scale;
	v->coord.x1 = x + v->delta.x - 2;
	v->coord.y1 = y + v->delta.y + scale;
	ft_drawline(v);
	draw_ant_legs(v, ant, scale, 0);
	draw_ant_legs(v, ant, scale, 1);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	display_ant_names(v);
}

void		display_square(VISU *v, int *ant, int width, int color)
{
	int col;
	int row;
	double x;
	double y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	y = v->ins->room[ant[CURRENT]].pos.y;
	v->delta.x = v->step * (v->ins->room[ant[NEXT]].pos.x - x) / 50.0;
	v->delta.y = v->step * (v->ins->room[ant[NEXT]].pos.y - y) / 50.0;
	if (width < 0)
	{
		x += v->delta.x;
		y += v->delta.y;
	}
	if (width < 0)
	{
		width *= -1;
		x += 5;
	}
	col = x - width;
	while (col < x + width)
	{
		row = y - width;
		while (row < y + width)
		{
			ft_put_to_img(v, row, col, color);
			++row;
		}
		++col;	
	}
}

void		detect_end(VISU *v)
{
	int ant;

	ant = -1;
	if (!v->ants)
		return ;
	while (++ant < v->ins->nb_ants)
	{
		if (v->ants[ant][1] == v->graphe->end)
		{
			v->ants[ant][0] = -1;
			v->ants[ant][1] = -1;
		}
	}

}


int		read_moves(VISU *v, char *line, int room)
{
	char **split;
	char **antsplit;
	int ant;
	int num;
	int	i;

	i = 0;
	if (!v->step)
		detect_end(v);
	if (!(split = ft_strsplit(line, ' ')))
		return (ERR_READ);
	ant = 0;
	if (!v || !v->ins)
		return (-1);
	while (split[i] && ++ant <= v->ins->nb_ants)
	{
//		ft_printf("error = %d split i = %s\n", v->error, split[i]);
		if (!(antsplit = ft_strsplit(split[i], '-')))
			return (ERR_READ);
//		ft_printf("antsplit0 = %s\n", (antsplit[0]));
		if (!(num = ft_atoi(antsplit[0] + 1)) && !(v->error = 1))
				return (0);
//		ft_printf("num = %d ant= %d\n", num, ant);
		if (num <= ant && num > 0)
		{

			if (v->ants[num - 1][CURRENT] != v->graphe->end)
				v->ants[num - 1][CURRENT] = v->ants[num - 1][NEXT];

			if (v->ants[num - 1][CURRENT] != v->graphe->start)
			{
				v->ants[num - 1][room] = get_room_index(v, antsplit[1], ft_strlen(antsplit[1]));
			}
		if (v->ants[num - 1][CURRENT] == -1 && v->ants[num - 1][NEXT] != -1)
			v->ants[num - 1][CURRENT] = v->graphe->start;
		ft_strdel(&antsplit[0]);
		ft_strdel(&antsplit[1]);
		ft_memdel((void **)&antsplit);
		ft_strdel(&split[i]);
			++i;
		}
		else if (v->ants[ant - 1][0] != -1 && v->ants[ant - 1][0] != v->graphe->end && v->ants[ant - 1][1] != v->graphe->end)
			v->ants[ant - 1][0] = v->ants[ant - 1][1];
	}
	ft_memdel((void **)&split);
	return (0);
}


void		display_anthill(t_list *anthill)
{
	t_list *tmp;

	tmp = anthill;
	while (tmp)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}


t_list	*ft_lstval(t_list *l, int index)
{
	int i;
	t_list *tmp;

	i = 0;
	tmp = l;
	while (i < index)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

void		print_movestab(int **ants, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < ants[i][0] + 1)
			ft_printf("%d ", ants[i][j]);
		ft_printf("\n");
	}
}

void		display_rooms(VISU *v)
{
	int	index[2];
	int i;

	i = -1;
	while ((unsigned int)++i < v->graphe->nb_rooms)
	{
		index[0] = i;
		index[1] = -1;
		display_square(v, (int *)&index, 10, COL_ROOM);
	}
}


void		display_ant_names(VISU *v)
{
	int ant;
	double x;
	double y;
	double deltax;
	double deltay;

	ant = 0;
	char *name;

	if (!v->ants)
		return ;
	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] && v->ants[ant][CURRENT] != -1 && v->ants[ant][CURRENT] != v->graphe->end)
		{
			x = v->ins->room[v->ants[ant][CURRENT]].pos.x;
			y = v->ins->room[v->ants[ant][CURRENT]].pos.y;
			deltax = v->step * (v->ins->room[v->ants[ant][NEXT]].pos.x - x) / 50.0;
			deltay = v->step * (v->ins->room[v->ants[ant][NEXT]].pos.y - y) / 50.0;
			name = ft_itoa(ant + 1);
			mlx_string_put(v->mlx, v->win, x + deltax + 10, y + deltay - 15, COL_ANTNAME, name);
			ft_strdel(&name);
		}
		++ant;
	}

}


int		display_moves(VISU *v, int color, int option)
{
	int ant;

	ant = 0;
	(void)color;
	(void)option;
	if (!v->ants)
		return (-1);
	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] && v->ants[ant][0] != -1 && v->ants[ant][0] != v->graphe->end)
		{
			display_ant(v, v->ants[ant], 4);
		}
		++ant;
	}
	return (0); 
}



void		move_next_room(int **paths, int ***ants, int nb_paths, int turn)
{
	int i;
	int ant;

	i = -1;
	while (++i < nb_paths)
	{
		ant = (*ants)[i][0];
		while (ant > 1)
		{
			(*ants)[i][ant] = (*ants)[i][ant - 1];
			--ant;
		}
		if (paths[i][turn] != -1 && (*ants)[i][2] != -1)
			(*ants)[i][1] = paths[i][turn];
		else
			(*ants)[i][1] = -1;

	}
}
