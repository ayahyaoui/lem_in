/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:09 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 21:42:49 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN__
#define __LEMIN__

#include "libft.h"
#include "lem_in.h"
# define ENV			t_environment
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define ERR_NB			22
# define NB_COMMANDS		2

# define NOINS			"empty file"
# define ANT_INPUT		"invalid ant format"
# define ANT_NB			"not enough ants!"
# define ANT_COMMAND	"invalid command for ant number"
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
# define SAME_START_END	"all ants are already at the end"
# define NOEND			"missing end indicator"
# define ROOM_CONF		"confusing room name, please avoid use of '-'"
# define MAXINT			"max number of ants is 2 147 483 647"
# define OPTION			"unknown option"
# define ARG			"unexpected argument, only options allowed"
# define LENGTH			"please specify tube length below 255"
# define NO_SOLUTION	"No valid path found between start and end"

# define OPTION_CHARS		"ctvw"
# define OPT_VERBOSE		1 << ('v' - 'a')
# define OPT_COLOR		1 << ('c' - 'a')
# define OPT_TURNS		1 << ('t' - 'a')
# define OPT_WAY		1 << ('w' - 'a')

# define COL_END		COL_CYAN


typedef struct s_file t_file;
typedef struct s_node t_node;


typedef struct		s_graphe
{
	unsigned int			nb_rooms; // anciennement taille
	unsigned int			nb_tubes;
	t_node					**node;
	int						*color;// char *
	int						*previous;// permet de trouver un chemin rapidement
	char					**map; // bientot capacite
	int						**graph;//prend  pas mal de place mais permet opti
	int						*capacite;
	int						start;
	int						end;
	int						nb_paths;
	int						start_next_to_end;
	t_file					*file;
}						t_graphe;

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

typedef struct		s_tab
{
	int			*tab;
	int			length;
}					t_tab;


typedef struct		s_environment
{
	t_list			*anthill;
	t_input			*ins;
	t_graphe		*graphe;
	t_tab ***		all_paths;
	int			**ants;
	int			nb_paths;
	int			options;
	int			type;
	int			turns;
	int			fd;
}					t_environment;

int		choose_method(t_graphe *g, ENV *info);
int		convert(t_graphe *g, ENV *infos);
void		free_graphe(t_graphe *g);


enum				e_type
{
	TYPE, NUMBER, ANTS, ROOM, TUBE, COMMENT, COMMAND
};

enum				e_special
{
	START, END
};

enum				e_input
{
	INVALID_INPUT, VALID_INPUT
};	

enum				e_direction
{
	FORWARD, BACKWARD, BOTH
};

enum				e_display
{
	DISPLAY_OFF, DISPLAY_ON
};

enum				e_error
{
	NO_ERR, ERR_NO_INS, ERR_READ, ERR_ANT_INPUT, ERR_ANT_NB, ERR_COMMAND, ERR_INTMAX,
   	ERR_ROOM, ERR_ROOM_CONF, ERR_COORD, ERR_TUBE, ERR_NOTUBE, ERR_NOROOM, ERR_DUP, ERR_ORDER,
	ERR_START, ERR_END, ERR_SAME, ERR_LIB, ERR_ALLOC, ERR_HELP, ERR_OPTION, ERR_ARG, ERR_SOLUTION 
};

int		scan_allmoves(ENV *e, int display);
void		display_besttab(t_tab ***tab);

int			set_env(ENV *e);
void			free_env(ENV *e);
void			free_strtab(char ***tab);
void			del_anthill(t_list *l);
char			*get_errmsg(int code);

int			is_dup(ENV *e, char *str, int max_index);

//TEMP
void		display_adj_mtrx(ENV *e, char **tab, int size);
void		print_rooms(ENV *e, char **rooms);



/*
** Display
*/

int			display(ENV *e, char *str);
void		display_moves(ENV *e, int **tab, int total);
void		display_anthill(t_list *anthill);
void		printlist(ENV *e, t_list *l);
int		ant_enter_path(ENV *e, t_tab ***paths, int comb);
void		move_next_room(ENV *e, t_tab ***paths);


int			read_options(ENV *e, char **argv, int argc);


/*
** Move ants in anthill
*/
int			ant_enter_path(ENV *e, t_tab ***paths, int comb);
void			move_next_room(ENV *e, t_tab ***paths);


/*
** Read and store instructions
*/

int			apply_commands(ENV *e);
int			get_ants(ENV *e, char **str, int type);
int			get_command(ENV *e, char *str, int option);
int			get_room(ENV *e, char **str);
int			get_tube(ENV *e, char **str, int way, int len);
int			store_rooms(ENV *e);
void			link_command(ENV *e, int type, int index);
int			read_instructions(ENV *e, char *str, int nbline, int ret);
int			setup_room_mtrx(ENV *e, int size);
char		sep(char *line, int *type);
char		**room_names(t_list *l, int nb_rooms, int **paths, int nb_paths);

/*
** Utils
*/

int			is_number(char *str);

#endif
