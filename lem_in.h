/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 21:20:34 by anyahyao         ###   ########.fr       */
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
/*
typedef struct				s_chemins
{
	unsigned char			*path;
	unsigned char			**all_path;
	unsigned int			nb_path;
	unsigned int			nb_max;
}							t_chemins;
*/
typedef struct				s_graphe
{
	int						taille;
	int						**map;
	int						*color;
	int						end;
	int						begin;
}							t_graphe;

typedef struct				s_tab
{
	int						length;
	int						*tab;
}							t_tab;

typedef struct				s_file
{
	int						begin;
	int						end;
	int						*tab;
}							t_file;

typedef struct				s_big_tab
{
	int						taille;
	int						*tab;
	int						*t1;
	int						*t2;
}							t_big_tab;

// new initial

//t_big_tab		*new_big_tab(t_graphe *g);
t_fusion		*create_fusion(t_path *p, int max);
int				*create_tab(int taille, int val);
int				**create_double_tab(int taille, int val);
t_graphe		*new_graphe(int taille);

// file.c
int				addfile(t_file *file, int value);
int				removefile(t_file *file);
int				isemptyfile(t_file *file);
t_file			*new_file(t_graphe *g);

// free.c
void			free_file(t_file **file);
void				free_graphe(t_graphe *g);

//affiche

int			displaypath(t_graphe *g, int *tab);
void		affiche_path(t_path *p);
void		printMultypath(int *res, int len);

int				dijistra(t_graphe *g);
int				**ft_tri_fusion_recursivecouple(unsigned int t1[][2], int len);
void				test_multipathbinary(t_graphe *g);
void				ft_mem_set_int(int *tab, int val, int taille);
void				tab_swap(int **a, int **b);
int					short_path(t_graphe *g, t_big_tab *bt, int begin, int end);
void				reboot_big_tab(t_big_tab *bt, int begin);
int					ajout_voisin(t_graphe *g, t_big_tab *bt, int k, int node);

#endif
