/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:09 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 15:31:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN__
#define __LEMIN__

#include "libft.h"
#include "visu.h"

# define ENV			t_environment
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define ERR_NB			21
# define NB_COMMANDS		2

# define NOINS			"empty file"
# define ANT_INPUT		"invalid ant format"
# define ANT_NB			"not enough ants!"
# define ROOM_INPUT		"invalid room format"
# define ROOM_DUP		"duplicate room name"
# define COORD			"non numerical values as room coordinates"
# define TUBE_INPUT		"invalid tube input"
# define NOTUBE			"missing corridors in anthill..."
# define TUBE_NOROOM	 "linking non-nexistant room"
# define ORDER			"invalid input order"
# define HELP			"(-h for usage)"
# define LIB			"failing lib function"
# define MALLOC			"failing malloc"
# define NOSTART		"missing start indicator"
# define NOEND			"missing end indicator"
# define ROOM_CONF		"confusing room name, please avoid use of '-'"
# define MAXINT			"max number of ants is 2 147 483 647"
# define OPTION			"unknown option"
# define ARG			"unexpected argument, only options allowed"
# define LENGTH			"please specify tube length below 255"

# define OPT_VERBOSE		1 << ('v' - 'a')
# define OPT_COLOR		1 << ('c' - 'a')
# define OPT_WAY		1 << ('w' - 'a')
# define OPT_LENGTH		1 << ('l' - 'a')




typedef struct		s_graphe
{
	unsigned int			nb_rooms; // anciennement taille
	unsigned int			nb_tubes;
	int				*color;
	char				**map;
	int				start;
	int				end;
}					t_graphe;

typedef struct		s_room
{
	char *name;
	t_4vect	pos; 
}					t_room;

typedef struct 		s_input
{
	int 			nb_ants;
	t_room			*room;
	int			**commands;
	int			nb_commands;
}					t_input;

:nt		choose_method(t_graphe *g);
void		free_graphe(t_graphe *g);


enum				e_type
{
	TYPE, NUMBER, ANTS, ROOM, TUBE, COMMENT, COMMAND
};

enum				e_special
{
	START, END
};

enum				e_status
{
	DEALT, UNDEALT
};

enum				e_input
{
	INVALID_INPUT, VALID_INPUT
};	

enum				e_direction
{
	FORWARD, BACKWARD, BOTH
};

enum				e_error
{
	NO_ERR, ERR_NO_INS, ERR_READ, ERR_ANT_INPUT, ERR_ANT_NB, ERR_INTMAX,
   	ERR_ROOM, ERR_ROOM_CONF, ERR_COORD, ERR_TUBE, ERR_NOTUBE, ERR_NOROOM, ERR_DUP, ERR_ORDER,
	ERR_START, ERR_END, ERR_LIB, ERR_ALLOC, ERR_HELP, ERR_OPTION, ERR_ARG, ERR_LENGTH 
};

int			set_env(VISU *v);
void			free_env(VISU *v);
void			free_strtab(char ***tab);
void			del_anthill(t_list *l);
char			*get_errmsg(int code);

int			is_dup(VISU *v, char *str, int max_index);

//TEMP
void		display_adj_mtrx(int **tab, int size);
void		print_rooms(VISU *v, char **rooms);



/*
** Display
*/

int			display(VISU *v, char *str);
void		display_moves(VISU *v, int **tab, int total);
void		display_anthill(t_list *anthill);
void		printlist(VISU *v, t_list *l);


int			read_options(VISU *v, char **argv, int argc);




/*
** Read and store instructions
*/

int			apply_commands(VISU *v);
int			get_ants(VISU *v, char **str, int type);
int			get_command(VISU *v, char *str, int option);
int			get_room(VISU *v, char **str);
int			get_tube(VISU *v, char **str, int way, int len);
int			store_rooms(VISU *e);
void			link_command(VISU *v, int type, int index);
int			read_instructions(VISU *v, char *str, int nbline, int ret);
int			setup_room_mtrx(VISU *v, int size);
char		sep(char *line, int *type);
char		**room_names(t_list *l, int nb_rooms, int **paths, int nb_paths);

/*
** Utils
*/

int			is_number(char *str);

#endif