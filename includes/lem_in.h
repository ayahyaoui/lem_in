/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/12 22:48:31 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN__
#define __LEM_IN__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lemin.h"

#define WHITE 0
#define GREY 1
#define BLACK 2
#define VALUE 0
#define NBNODE 1
#define COST 1
#define ERRORMALLOC 12
#define MIN(a, b) (a > b ? b : a)
#include "libft.h"



/*
** t_path contiendra tout les chemin different possible en binaire
**					-path est le tableau de chemin termine tailleMax (2^13)
**					-nb_path est la taille du tableau path
**					-nb_next_node
*/
typedef struct			s_graphe t_graphe;

typedef struct			s_point
{
	int						value;
	int						len;
}							t_point;

typedef struct				s_path
{
	unsigned int		path[9000][2];
	unsigned int		nb_path;
}						t_path;

typedef struct			s_breakdown
{
	unsigned int		value;
	unsigned int		cost;
	unsigned int		*breakdown;
	unsigned int		len;
}						t_breakdown;

typedef struct			s_fusion
{
	t_breakdown		**fusion;// taille a calculer 
	unsigned int	nb_path;
	unsigned int	altern;
}					t_fusion;

typedef struct			s_node
{
	int value;
	int previous;
	int color;
	int parent; // aciennement capaite
}						t_node;

typedef struct		s_tab t_tab;

typedef struct		s_file
{
	int				begin;
	int				end;
	int				*tab;
}					t_file;

typedef struct		s_big_tab
{
	unsigned  int				taille;
	int				*tab;
	int				*t1;
	int				*t2;
}					t_big_tab;



typedef struct 		s_environment	t_environment;
# define ENV			t_environment
typedef struct 		s_input					t_input;



void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
t_tab		***registerPath(t_graphe *g, int nbPath, t_tab ***besttab);
t_tab		***allowBestTab(int nbPath);
void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
int			algoopti(t_graphe *g, ENV *e);
void		print_lastpath(t_graphe *g, t_input *infos);
int			edmond_karp(t_graphe *g, t_tab ***t);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);
void		convertGraphe(t_graphe *g);
void		cleanNodee(t_graphe *g);
void		add_node_parcous(t_graphe *g, t_node *next, int value, int opt);
int			convert_graphe(t_graphe *g);






int		is_break_path(t_graphe *g, int start);
void	add_node_parcous(t_graphe *g, t_node *next, int value, int opt);
void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
t_tab	***registerPath(t_graphe *g, int nbPath, t_tab ***besttab);
t_tab	***allowBestTab(int nbPath);
void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
int			algoopti(t_graphe *g, ENV *e);
void		print_lastpath(t_graphe *g, t_input *infos);
int			edmondKarp(t_graphe *g, t_tab ***t);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);
void	convertGraphe(t_graphe *g);
void	cleanNodee(t_graphe *g);














// new initial

int			displayallpath(t_graphe *g, t_tab ***t);

//t_big_tab			*new_big_tab(t_graphe *g);
t_fusion			*create_fusion(t_path *p, int max);
int					*create_tab(int taille, int val);
char				**create_double_tab(int taille, int val);
t_graphe			*new_graphe(int taille);

// file.c
int					addfile(t_file *file, int value);
int					removefile(t_file *file);
int					isemptyfile(t_file *file);
t_file				*new_file(t_graphe *g);
t_file				*clean_file(t_file *file, int size);
void	printfile(t_file *f);

// free.c
void				free_fusion(t_fusion *f);
void				free_file(t_file **file);
void				free_graphe(t_graphe *g);
void				free_besttab(t_tab ***best_tab);
void				free_t_tab(t_tab *t);

//affiche
void				affichebreak(t_breakdown *bp);
void				infos(t_fusion *f);
int					displaypath(t_graphe *g, int *tab);
void				affiche_path(t_graphe *g, t_path *p);
void				printMultypath(int *res, int len);
//int					displayallpath(t_graphe *g, t_tab ***t);

// fusion.c

int					valueisinfusion(t_fusion *fusion, unsigned int value);
int					getfusionpath(t_breakdown *b, int *res, unsigned int val,
					int cost);
int					fusion_path(t_fusion *f, unsigned int t[2], t_breakdown *c);
void				ft_swapPointeur(t_fusion **a, t_fusion **b);

// binarypath

int					number_active_bit(unsigned long p, int max);
//t_tab				***test_multipathbinary(t_graphe *g);
void				getallpath(t_graphe *g, t_path *path, int node
					, unsigned int p);

int					degre_graphe(t_graphe *g);
int					degre(t_graphe *g, int node);


//count_ant

//int			add_ant(t_graphe *g, t_tab ***best_tab, int nb_ant);



int				dijistra(t_graphe *g);
int				**ft_tri_fusion_recursive_couple(unsigned int t1[][2], int len);
//t_tab				***test_multipathbinary(t_graphe *g);
void				ft_mem_set_int(int *tab, int val, int taille);
void				tab_swap(int **a, int **b);
int					short_path(t_graphe *g, t_big_tab *bt, unsigned int begin, unsigned int end);
void				reboot_big_tab(t_big_tab *bt, int begin);
int					ajout_voisin(t_graphe *g, t_big_tab *bt, int k, int node);

#endif
