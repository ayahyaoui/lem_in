/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/13 18:58:55 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char			sep(char *line, int *type)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(line);
	while (++i < len)
		if (line[i] == '-' && (*type = TUBE))
			return ('-');
	*type = ROOM;
	return (' ');
}

int				dispatch_ins(VISU *v, char **words, int nb)
{
	int ret;
	static int		endrooms;

	ret = NO_ERR;
	if (nb == 1)
	{
		ret = get_ants(v, words, v->type);
		return (ret);
	}
	else if (v->type == ROOM && !endrooms)
		ret = get_room(v, words);
	else if (v->type == TUBE && ++endrooms)
	{
		if (endrooms == 1)
		{
			ret = store_rooms(v);
			if (ret || (ret = setup_room_mtrx(v, v->graphe->nb_rooms)))
				return (ret);
		}
		ret = get_tube(v, words, BOTH, 1);
	}
	else
		return (ERR_ORDER);
	return (ret);
}

void			display_everything(VISU *v, char *turn)
{
		display_rooms(v);
		display_moves(v, COL_ANT, 0);
		mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x + 13, v->ins->room[v->graphe->start].pos.y - 10, COL_TUBES, "START");
		mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x + 13, v->ins->room[v->graphe->end].pos.y - 10, COL_TUBES, "END");
		mlx_string_put(v->mlx, v->win, 20, 50, 0xFFFFFF, "Turn # ");
		mlx_string_put(v->mlx, v->win, 100, 50, 0xFFFFFF, turn);
}



int				anim_moves(VISU *v)
{
	char *str = NULL;
	static int iter; 
	static int	turn = -1;
	char	turn_str[11];
	int		ret;

	ret = 1;
//	ft_printf("ANIM MOVES\n");
	if (!v->pause)
	{
		if (v->step > SPEED)
			v->step = 0;
		ft_bzero(v->img.ptr, v->win_w * v->win_h * sizeof(int));
		if (!v->step)
		{
			if (!iter && get_next_line2(STDIN, &str) && !str)
				return (ERR_LIB);
			read_moves(v, str, NEXT);
			ft_strdel(&str);
			++turn;
		}
		ft_points_to_img(v);
		ft_itoa_mod(turn_str, turn);
		display_everything(v, (char *)turn_str);
//		display_rooms(v);
//		display_moves(v, COL_ANT, 0);
//		mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x + 13, v->ins->room[v->graphe->start].pos.y - 10, COL_TUBES, "START");
//		mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x + 13, v->ins->room[v->graphe->end].pos.y - 10, COL_TUBES, "END");
//		mlx_string_put(v->mlx, v->win, 20, 50, 0xFFFFFF, "Turn # ");
//		mlx_string_put(v->mlx, v->win, 100, 50, 0xFFFFFF, turn_str);
		usleep(10000 * v->speed);

		++v->step;
		return (NO_ERR);
	}
		display_everything(v, (char *)turn_str);
//	display_moves(v, COL_ANT, 0);
//	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
//	display_ant_names(v);
//	mlx_hook(v->win, KeyPress, KeyPressMask, ft_dealkey, (void *)v);
//	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x + 13, v->ins->room[v->graphe->start].pos.y - 10, COL_TUBES, "START");
//	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x + 13, v->ins->room[v->graphe->end].pos.y - 10, COL_TUBES, "END");
	return (NO_ERR);
}

int				read_instructions(VISU *v, char *str, int nbline, int ret)
{
	char			**words;
	char			*tmp;
	t_list			*line;

	while (!ret && get_next_line2(STDIN, &str) > 0 && str && str[0] != 0)
	{
		if (str[0] != '#' && ++nbline)
		{
			if (!(words = ft_strsplit(str, sep(str, &v->type))))
			{
				ft_strdel(&str);
				return (ERR_READ);
			}
			dispatch_ins(v, words, nbline);
			free_strtab(&words);
		}
		else if (str[1] == '#' && get_command(v, str, 0))
			++v->ins->nb_commands;
		line = ft_lstnew(tmp = ft_strdup(str), ft_strlen(str) + 1);
		ft_strdel(&tmp); 
		ft_lstaddend(&v->anthill, line);
		ft_strdel(&str);
	}
//	ft_printf("1nd HALF READ\n");
	ft_strdel(&str);
	return (NO_ERR);
}
