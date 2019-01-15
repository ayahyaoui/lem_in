/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:09 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 22:21:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN__
#define __LEMIN__

#include "libft.h"
#include "lem_in.h"
#include "color.h"

# define ENV			t_environment
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define NB_COMMANDS		2

/*
** ERRORS
*/

# define NB_ERRORS		11
# define NOINS			"empty file"
# define ANT_INPUT		"invalid ant format (require strictly postiive value)"
# define ANT_NB			"not enough ants!"
# define NOTUBE			"missing corridors in anthill..."
//# define ORDER			"invalid input order"
# define NOSTART		"missing start indicator"
# define NOEND			"missing end indicator"
# define SAME_START_END		"all ants are already at the end"
# define LIB			"failing lib function"
# define MALLOC			"failing malloc"
# define ARG			"unexpected argument, only options allowed"
# define NO_SOLUTION		"No valid path found between start and end"

/*
** WARNINGS
*/

# define NB_WARNINGS		16
# define MAXINT			"max number of ants is 2 147 483 647"
# define ROOM_INPUT		"invalid room format"
# define ROOM_CONF		"confusing room name, please avoid use of '-'"
# define ROOM_DUP		"duplicate room name"
# define ROOM_CHAR		"invalid character in room name (L)"
# define COORD			"non numerical values as room coordinates"
# define TUBE_NOROOM		"linking non-nexistant room"
# define TUBE_INPUT		"invalid tube input"
# define INVALID_INPUT		"invalid input"
# define HELP			"(-h for usage)"
# define OPTION			"unknown option"
# define FAILED_START		"command ##start without effect"
# define FAILED_END		"command ##end without effect"
# define DOUBLE_START		"start room already set, replacing value"
# define DOUBLE_END		"end room already set, replacing value"
# define SAME_ROOM		"link to itself is without effect"

/*
** OPTIONS
*/

# define OPTION_CHARS		"chtvw"
# define OPTION_WIDTH		10
# define OPT_V_CHAR		'v'
# define OPT_V_DESCRIPTION	"Display warnings and error details"
# define OPT_VERBOSE		1 << ('v' - 'a')
# define OPT_C_CHAR		'c'
# define OPT_C_DESCRIPTION	"Activate colored output"
# define OPT_COLOR		1 << ('c' - 'a')
# define OPT_H_CHAR		'h'
# define OPT_H_DESCRIPTION	"Display anthill instructions and available options"
# define OPT_HELP		1 << ('h' - 'a')
# define OPT_T_CHAR		't'
# define OPT_TURNS		1 << ('t' - 'a')
# define OPT_T_DESCRIPTION	"Display total number of turns"
# define OPT_WAY		1 << ('w' - 'a')

/*
** COMMANDS
*/

# define NB_COMMANDS		2
# define COMMAND_START		"##start"
# define START_DESCRIPTION	"set room as start location"
# define COMMAND_END		"##end"
# define END_DESCRIPTION	"set room as end location"


# define HELP_TITLE		"*** Rules for setting up anthill ***"
# define COMMENTS_NAME		"comments"
# define COMMENTS_DESCRIPTION	"lines starting with #"
# define COMMENTS_PLACEMENT	"anywhere"
# define COMMENTS_EXAMPLE	"Example: #This is a comment"
# define COMMANDS_NAME		"commands"
# define COMMANDS_DESCRIPTION	"lines starting with ##"
# define COMMANDS_PLACEMENT	"before a significant value"
# define COMMANDS_EXAMPLE	"##command"
# define COMMANDS_NB1		"if next input is outside the command scope, "
# define COMMANDS_NB2		"the command will have no effect."
# define COMMANDS_AVAILABLE	"available commands"
# define ANTS_NAME		"number of ants"
# define ANTS_DESCRIPTION	"strictly positive value"
# define ANTS_PLACEMENT		"at the top of the file"
# define ANTS_EXAMPLE		"Example: 16"
# define ROOM_NAME		"rooms"
# define ROOM_DESCRIPTION	"room name followed by two integer coordinates"
# define ROOM_PLACEMENT		"after ant number, before tubes information"
# define ROOM_EXAMPLE		"room_Name 5 4"
# define ROOM_NB1		"a room name cannot start with L or #"
# define ROOM_NB2		"forbidden character: -"
# define TUBE_NAME		"tubes"
# define TUBE_DESCRIPTION	"link between two existing rooms"
# define TUBE_PLACEMENT		"after rooms"
# define TUBE_FORWARD		"forward direction: ->"
# define TUBE_BACKWARD		"backward direction: <-"
# define TUBE_ANYWAY		"any direction: - or <->"
# define TUBE_EXAMPLE		"room1-other_room"




typedef struct s_file t_file;
typedef struct s_node t_node;


typedef struct			s_graphe
{
	unsigned int		nb_rooms; // anciennement taille
	unsigned int		nb_tubes;
	t_node			**node;
	int			*color;// char *
	int			*previous;// permet de trouver un chemin rapidement
	char			**map; // bientot capacite
	int			**graph;//prend  pas mal de place mais permet opti
	int			*capacite;
	int			start;
	int			end;
	int			nb_paths;
	int			start_next_to_end;
	t_file			*file;
}				t_graphe;

typedef struct			s_room
{
	char			*name;
	t_4vect			pos; 
}				t_room;

typedef struct 			s_input
{
	int 			nb_ants;
	t_room			*room;
	int			**commands;
	int			nb_commands;
}				t_input;

typedef struct			s_tab
{
	int			*tab;
	int			length;
}				t_tab;


typedef struct			s_environment
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
}				t_environment;


enum				e_error
{
	NO_ERR, ERR_NO_INS, ERR_ANT_INPUT, ERR_ANT_NB,
   	ERR_NOTUBE, ERR_START, ERR_END, ERR_SAME, ERR_LIB, ERR_ALLOC, ERR_ARG, ERR_SOLUTION,
	NO_WRNG, WRNG_INTMAX, WRNG_ROOM, WRNG_ROOM_CONF, WRNG_DUP, WRNG_ROOM_CHAR, WRNG_COORD,
	WRNG_TUBE_NOROOM, WRNG_TUBE, WRNG_INPUT, WRNG_HELP, WRNG_OPTION, WRNG_FAILED_START, WRNG_FAILED_END,
	WRNG_DOUBLE_START, WRNG_DOUBLE_END, WRNG_SAME_ROOM,

};

enum				e_type
{
	TYPE, NUMBER, ANTS, ROOM, TUBE, COMMENT, COMMAND
};

enum				e_special
{
	START, END
};

enum				e_direction
{
	FORWARD, BACKWARD, BOTH
};

enum				e_display
{
	DISPLAY_OFF, DISPLAY_ON
};

//int		choose_method(t_graphe *g, ENV *info);
//int		convert(t_graphe *g, ENV *infos);
//void		display_besttab(t_tab ***tab);

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

int		is_failing_error(int err);
int		display_error(ENV *e, int code);
int		display_warning(ENV *e, int code);
void		display_help(char *col1, char *col2);

void		display_moves(ENV *e, int **tab, int total);
void		display_anthill(t_list *anthill);
void		printlist(ENV *e, t_list *l);
int		ant_enter_path(ENV *e, t_tab ***paths, int comb);
void		move_next_room(ENV *e, t_tab ***paths);


int			read_options(ENV *e, char **argv, int argc);

/*
** Memory and set-up
*/

void		free_graphe(t_graphe *g);


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
void			link_command(ENV *e, int type, int index);
int			read_instructions(ENV *e, char *str, int nbline, int ret);
char			**room_names(t_list *l, int nb_rooms, int **paths, int nb_paths);
int			setup_room_mtrx(ENV *e, int size);
char			sep(char *line, int *type);
int			store_rooms(ENV *e);

/*
** Find solution
*/

int		scan_allmoves(ENV *e, int display);

/*
** Utils
*/

int			is_number(char *str);


#endif
