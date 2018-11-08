/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:26:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 20:31:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_movement_txt(ENV *e)
{
	mlx_string_put(e->mlx, e->win, 155, e->menu.gap0 + 0, e->txt, "[8]");
	mlx_string_put(e->mlx, e->win, 140, e->menu.gap0 + 35, e->title, "ROTATE");
	mlx_string_put(e->mlx, e->win, 155, e->menu.gap0 + 70, e->txt, "[2]");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap0 + 35, e->txt, "[4]");
	mlx_string_put(e->mlx, e->win, 225, e->menu.gap0 + 35, e->txt, "[6]");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap1 + 120, e->txt, "[-]");
	mlx_string_put(e->mlx, e->win, 150, e->menu.gap1 + 120, e->title, "ZOOM");
	mlx_string_put(e->mlx, e->win, 225, e->menu.gap1 + 120, e->txt, "[+]");
	mlx_string_put(e->mlx, e->win, 165, e->menu.gap2 + 170, e->txt, "^");
	mlx_string_put(e->mlx, e->win, 165, e->menu.gap2 + 175, e->txt, "|");
	mlx_string_put(e->mlx, e->win, 150, e->menu.gap2 + 210, e->title, "MOVE");
	mlx_string_put(e->mlx, e->win, 225, e->menu.gap2 + 210, e->txt, "-");
	mlx_string_put(e->mlx, e->win, 230, e->menu.gap2 + 210, e->txt, ">");
	mlx_string_put(e->mlx, e->win, 100, e->menu.gap2 + 210, e->txt, "-");
	mlx_string_put(e->mlx, e->win, 95, e->menu.gap2 + 210, e->txt, "<");
	mlx_string_put(e->mlx, e->win, 165, e->menu.gap2 + 245, e->txt, "|");
	mlx_string_put(e->mlx, e->win, 165, e->menu.gap2 + 250, e->txt, "v");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap2 + 270, e->txt, "INVERT");
	mlx_string_put(e->mlx, e->win, 220, e->menu.gap2 + 270, e->txt, "[I]");
}

static void	ft_height_txt(ENV *e)
{
	mlx_string_put(e->mlx, e->win, 140, e->menu.gap3 + 320, e->title, "CHANGE");
	mlx_string_put(e->mlx, e->win, 140, e->menu.gap3 + 340, e->title, "HEIGHT");
	mlx_string_put(e->mlx, e->win, 75, e->menu.gap3 + 330, e->txt, "[PGUP]");
	mlx_string_put(e->mlx, e->win, 205, e->menu.gap3 + 330, e->txt, "[PGDW]");
}

static void	ft_color_txt(ENV *e)
{
	mlx_string_put(e->mlx, e->win, 140, e->menu.gap4 + 390, e->title, "COLORS");
	mlx_string_put(e->mlx, e->win, 140, e->menu.gap4 + 440, e->txt, "ROTATE");
	mlx_string_put(e->mlx, e->win, 75, e->menu.gap4 + 440, e->txt, "[HOME]");
	mlx_string_put(e->mlx, e->win, 205, e->menu.gap4 + 440, e->txt, "[END]");
	mlx_string_put(e->mlx, e->win, 150, e->menu.gap4 + 490, e->txt, "MODE");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap4 + 510, e->txt, "MAP");
	mlx_string_put(e->mlx, e->win, 220, e->menu.gap4 + 510, e->txt, "[M]");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap4 + 530, e->txt, "BASIC");
	mlx_string_put(e->mlx, e->win, 220, e->menu.gap4 + 530, e->txt, "[C]");
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap4 + 550, e->txt,
			"TOGGLE VEGAS");
	mlx_string_put(e->mlx, e->win, 220, e->menu.gap4 + 550, e->txt, "[V]");
}

int			ft_menu_txt(ENV *e)
{
	static int iteration;

	if (!iteration)
	{
		e->menu.gap0 = (e->win_h - MIN_W - 100) * 0.15;
		e->menu.gap1 = 2 * e->menu.gap0;
		e->menu.gap2 = 3 * e->menu.gap0;
		e->menu.gap3 = 4 * e->menu.gap0;
		e->menu.gap4 = 5 * e->menu.gap0;
		e->menu.gap5 = 6 * e->menu.gap0;
		e->menu.gap6 = 7 * e->menu.gap0;
		e->menu.gap7 = 8 * e->menu.gap0;
		e->title = COL_TITLE;
		e->txt = COL_TXT;
	}
	++iteration;
	ft_movement_txt(e);
	ft_height_txt(e);
	ft_color_txt(e);
	mlx_string_put(e->mlx, e->win, 85, e->menu.gap5 + 580, e->title, "RESET");
	mlx_string_put(e->mlx, e->win, 220, e->menu.gap5 + 580, e->title, "[R]");
	return (0);
}

int			ft_display_menu(ENV *e)
{
	int row;
	int col;
	int offset;

	offset = 0;
	col = MENU_START;
	while (col <= MENU_END)
	{
		row = 0;
		while (row < e->win_h)
		{
			ft_put_to_img(e, row, col, COL_BCKGRND);
			++row;
		}
		++col;
	}
	return (0);
}
