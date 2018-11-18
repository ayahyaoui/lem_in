/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/16 21:12:23 by emuckens         ###   ########.fr       */
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


int				anim_moves(VISU *v)
{
	char *str = NULL;
	int	ret = 0;
//	ft_printf("ANIM MOVES\n");
//	v->ants = (int *)ft_memalloc(sizeof(int) * (v->ins->nb_ants + 1));	
	if (!v->pause && !ret && get_next_line2(STDIN, &str) > 0 && str)
	{
		ft_bzero(v->img.ptr, v->win_w * v->win_h * 4);
//		ft_printf("check str = %s\n", str)
		ft_points_to_img(v);
		display_rooms(v);
//		display_moves(v, COL_ROOM, 1);
		read_moves(v, str);
		display_moves(v, COL_ANT, 0);
		mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
		display_ant_names(v);
		sleep(1);
		ft_strdel(&str);
	}
	mlx_hook(v->win, KeyPress, KeyPressMask, ft_dealkey, (void *)v);

//	ft_strdel(&str);
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
