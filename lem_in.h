/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2018/09/30 21:01:08 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN__
#define __LEM_IN__
#include <stdio.h>

#include "libft/includes/libft.h"


typedef struct	s_graphe
{
	int			taille;
	int			**map;
}				t_graphe;

typedef struct	s_big_tab
{
	int			taille;
	int			*tab;
	int			*t1;
	int			*t2;
}				t_big_tab;

void	free_graphe(t_graphe *g);
void			ft_mem_set_int(int *tab, int val, int taille);
int		*create_tab(int taille, int val);
void	tab_swap(int **a, int **b);
int		**create_double_tab(int taille, int val);
t_big_tab		*new_big_tab(t_graphe *g);
int				short_path(t_graphe *g, t_big_tab *bt, int begin, int end);
void			reboot_big_tab(t_big_tab *bt, int begin);
int		ajout_voisin(t_graphe *g, t_big_tab *bt, int k, int node);

#endif
