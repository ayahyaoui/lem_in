/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:27 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 06:28:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include "lemin.h"
# include "libft.h"

# define WHITE 0
# define GREY 1
# define BLACK 2
# define VALUE 0
# define NBNODE 1
# define COST 1
# define ERRORMALLOC 12
# define PATH_SIZE 2
# define ENV t_environment

typedef struct s_environment	t_environment;
typedef struct s_input	t_input;
typedef struct s_graphe	t_graphe;
typedef struct s_tab	t_tab;

typedef struct	s_point
{
	int			value;
	int			len;
}				t_point;

typedef struct	s_node
{
	int			value;
	int			previous;
	int			color;
	int			parent;
}				t_node;

typedef struct	s_file
{
	int			begin;
	int			end;
	int			*tab;
}				t_file;

t_node			*create_node(int value);
int				**create_double_int_tab(int taille, int val);
int				*create_tab(int taille, int val);
t_tab			***create_besttab(int nbpath);

void			clean_node(t_graphe *g);
int				convert_graphe(t_graphe *g);

int				addfile(t_file *file, int value);
int				removefile(t_file *file);
int				isemptyfile(t_file *file);
t_file			*new_file(t_graphe *g);
t_file			*clean_file(t_file *file, int size);

int				find_best_soluion(t_graphe *g, ENV *e);
int				edmond_karp(t_graphe *g, t_tab ****t);
int				ajout_chemins(t_graphe *g);
void			add_node_parcous(t_graphe *g, t_node *next, int value, int opt);
int				is_break_path(t_graphe *g, int start);

t_tab			***register_path(t_graphe *g, int nbpath, t_tab ***besttab);
int				sort_path(t_graphe *g);

int				place_ant(t_tab ***besttab, int fourmis, int path);
void			change_place_ant(t_graphe *g, int *tab);
int				*prediction(ENV *e, t_graphe *g);
int				try_to_place_ant(t_tab ***besttab, int *tab_fourmis);
void			clean_ant(t_tab ***besttab);

void			free_file(t_file **file);
void			free_graphe(t_graphe *g);
void			free_besttab(t_tab ***best_tab);
void			free_t_tab(t_tab *t);

void			*ft_realloc(void *previous, size_t t, size_t len_src);
int				displayallpath(t_graphe *g, t_tab ***t);

#endif
