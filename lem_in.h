/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/21 23:17:36 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN__
#define __LEM_IN__
#include <stdio.h>

#define WHITE 0
#define GREY 1
#define BLACK 2
#define VALUE 0
#define NBNODE 1
#define COST 1
#define MIN(a, b) (a > b ? b : a)
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"


/*
** t_path contiendra tout les chemin different possible en binaire
**					-path est le tableau de chemin termine tailleMax (2^13)
**					-nb_path est la taille du tableau path
**					-nb_next_node
*/

typedef struct				s_point
{
	int						value;
	int						len;
}							t_point;

typedef struct				s_path
{
	unsigned int			path[9000][2];
	unsigned int			nb_path;
//	int						next_node;  
//	int						nb_next_node;
}							t_path;

typedef struct				s_breakdown
{
	unsigned int			value;
	unsigned int			cost;
	unsigned int			*breakdown;
	unsigned int			len;
}							t_breakdown;

typedef struct				s_fusion
{
	t_breakdown				**fusion;// taille a calculer 
	unsigned int			nb_path;
	unsigned int			altern;

}							t_fusion;

typedef struct		s_chemins
{
	unsigned char	*path;
	unsigned char	**all_path;
	unsigned int	nb_path;
	unsigned int	nb_max;
}					t_chemins;

typedef struct		s_graphe
{
	int				taille;
	int				**map;
	int				*color;
	int				end;
}					t_graphe;

typedef struct		s_big_tab
{
	int				taille;
	int				*tab;
	int				*t1;
	int				*t2;
}					t_big_tab;

int				**ft_tri_fusion_recursivecouple(unsigned int t1[][2], int len);
void				test_init_all_path(t_graphe *g, int end);
void				free_graphe(t_graphe *g);
void				ft_mem_set_int(int *tab, int val, int taille);
int					*create_tab(int taille, int val);
void				tab_swap(int **a, int **b);
int					**create_double_tab(int taille, int val);
t_big_tab			*new_big_tab(t_graphe *g);
int					short_path(t_graphe *g, t_big_tab *bt, int begin, int end);
void				reboot_big_tab(t_big_tab *bt, int begin);
int					ajout_voisin(t_graphe *g, t_big_tab *bt, int k, int node);

#endif
