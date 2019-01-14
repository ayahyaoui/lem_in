/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 14:58:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <unistd.h>

int		main(void)
{
	static VISU	v;
	int		err;
	int		i;

	i = -1;
	set_env(&v);
	if ((err = read_instructions(&v, NULL, 0, 0)))
	{
		return (display(&v, get_errmsg(err)));
	}
	if ((err = apply_commands(&v)))
	{
		return (display(&v, get_errmsg(err)));
	}
	ft_init_win(&v);
	ft_get_img(&v);
	ft_transform_points((void *)&v);
	display_everything(&v);
//	ft_points_to_img(&v);
//	display_rooms(&v);
//	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	v.map = (int *)ft_memalloc(sizeof(int) * v.win_h * v.win_w);
	v.ants = (int **)ft_memalloc(sizeof(int *) * (v.ins->nb_ants + 1));

	while (++i < v.ins->nb_ants)
	{
		if (!(v.ants[i] = (int *)ft_memalloc(sizeof(int) * 2)))
			return (ERR_ALLOC);
		v.ants[i][0] = -1;
		v.ants[i][1] = -1;
	}

	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
	mlx_loop(v.mlx);

	return (0);
}

