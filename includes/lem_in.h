/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/15 17:48:29 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN__
#define __LEM_IN__
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
#define PATH_SIZE 2
# define ENV			t_environment
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


typedef struct 		s_environment	t_environment;
typedef struct 		s_input					t_input;




t_node			*create_node(int value);
int			find_path_bonus(t_tab ***besttab, t_graphe *g);
void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
t_tab		***registerPath(t_graphe *g, int nbPath, t_tab ***besttab);
t_tab		***allowBestTab(int nbPath);
void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
int			algoopti(t_graphe *g, ENV *e);
void		print_lastpath(t_graphe *g, t_input *infos);
int			edmond_karp(t_graphe *g, t_tab ****t);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);
void		convertGraphe(t_graphe *g);
void		add_node_parcous(t_graphe *g, t_node *next, int val, int opt);
int			convert_graphe(t_graphe *g);
int		place_ant(t_tab ***besttab, int fourmis, int path);

void					*ft_realloc(void *previous, size_t t, size_t len_src);


int		try_to_place_ant(t_tab ***besttab, int *tab_fourmis);
void		clean_ant(t_tab ***besttab);

int	prediction(ENV *e, t_graphe *g);


int		is_break_path(t_graphe *g, int start);
void	add_node_parcous(t_graphe *g, t_node *next, int value, int opt);
void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
t_tab	***allowBestTab(int nbPath);
void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
int			algoopti(t_graphe *g, ENV *e);
void		print_lastpath(t_graphe *g, t_input *infos);
int			edmondKarp(t_graphe *g, t_tab ***t);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);

void	convertGraphe(t_graphe *g);
void	clean_node(t_graphe *g);


int				**creategraph(int len);
int				*create_tab(int taille, int val);
int			**create_double_int_tab(int taille, int val);





// file.c
int					addfile(t_file *file, int value);
int					removefile(t_file *file);
int					isemptyfile(t_file *file);
t_file				*new_file(t_graphe *g);
t_file				*clean_file(t_file *file, int size);
void	printfile(t_file *f);

// free.c
void				free_file(t_file **file);
void				free_graphe(t_graphe *g);
void				free_besttab(t_tab ***best_tab);
void				free_t_tab(t_tab *t);

int			displayallpath(t_graphe *g, t_tab ***t);


/*
// new initial


t_graphe			*new_graphe(int taille);

//affiche
int					displaypath(t_graphe *g, int *tab);
void				affiche_path(t_graphe *g, t_path *p);
void				printMultypath(int *res, int len);
//int					displayallpath(t_graphe *g, t_tab ***t);
//count_ant

//int			add_ant(t_graphe *g, t_tab ***best_tab, int nb_ant);



int				dijistra(t_graphe *g);
int				**ft_tri_fusion_recursive_couple(unsigned int t1[][2], int len);
//t_tab				***test_multipathbinary(t_graphe *g);
void				ft_mem_set_int(int *tab, int val, int taille);
void				tab_swap(int **a, int **b);
a*/
#endif
