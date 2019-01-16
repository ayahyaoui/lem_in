/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:09 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 21:11:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN__
#define __LEM_IN__

# include "libft.h"
# include "color.h"

# define ENV			t_environment

# define STDIN				0
# define STDOUT				1
# define STDERR				2

/*
** ALGORITHM TOOLS
*/

# define WHITE				0
# define GREY				1
# define BLACK				2
# define VALUE				0
# define NBNODE				1
# define COST				1
# define PATH_SIZE			2

/*
** ERRORS
*/

# define NB_ERRORS			10
# define NOINS				"no instruction received"
# define ANT_NB				"no valid ant number!"
# define NOTUBE				"missing corridors in anthill..."
# define NOSTART			"missing start indicator"
# define NOEND				"missing end indicator"
# define SAME_START_END		"all ants are already at the end"
# define LIB				"failing lib function"
# define MALLOC				"failing malloc"
# define ARG				"unexpected argument, only options allowed"
# define NO_SOLUTION		"No valid path found between start and end"

/*
** WARNINGS
*/

# define NB_WARNINGS		19
# define ANT_INPUT			"invalid ant format (need strictly positive value)"
# define MAXINT				"max value is 2 147 483 647"
# define MININT				"min value is -2 147 483 648"
# define ROOM_INPUT			"invalid room format"
# define ROOM_CONF			"confusing room name, please avoid use of '-'"
# define ROOM_DUP			"duplicate room name"
# define ROOM_CHAR			"invalid character in room name (L)"
# define COORD				"non numerical values as room coordinates"
# define TUBE_NOROOM		"linking non-nexistant room"
# define TUBE_INPUT			"invalid tube input"
# define INVALID_INPUT		"invalid input"
# define HELP				"(-h for usage)"
# define OPTION				"unknown option"
# define FAILED_START		"command ##start without effect"
# define FAILED_END			"command ##end without effect"
# define DOUBLE_START		"start room already set, replacing value"
# define DOUBLE_END			"end room already set, replacing value"
# define SAME_ROOM			"link to itself is without effect"

/*
** OPTIONS
*/

# define OPTION_CHARS		"chtvw0123456789"
# define OPTION_WIDTH		10
# define OPT_VERBOSE		1 << ('v' - 'a')
# define OPT_COLOR			1 << ('c' - 'a')
# define OPT_TURNS			1 << ('t' - 'a')
# define OPT_HELP			1 << ('h' - 'a')
# define OPT_WAY			1 << ('w' - 'a')
# define OPT_C_DESCRIPTION	"Activate colored output"
# define OPT_H_DESCRIPTION	"Display anthill instructions and available options"
# define OPT_T_DESCRIPTION	"Display total number of turns"
# define OPT_V_DESCRIPTION	"Display warnings and error details"

/*
** COMMANDS
*/

# define NB_COMMANDS		2
# define COMMAND_START		"##start"
# define START_DESCRIPTION	"set room as start location"
# define COMMAND_END		"##end"
# define END_DESCRIPTION	"set room as end location"

/*
** HELP DISPLAY
*/

# define HELP_TITLE			"*** Rules for setting up anthill ***"
# define COMMTS_NAME		"comments"
# define COMMTS_DESCRIPTION	"lines starting with #"
# define COMMTS_PLACEMENT	"anywhere"
# define COMMTS_EX			"Example: #This is a comment"
# define COMMDS_NAME		"commands"
# define COMMDS_DESCRIPTION	"lines starting with ##"
# define COMMDS_PLACEMENT	"before a significant value"
# define COMMDS_EX			"##command"
# define COMMDS_NB1			"if next input is outside the command scope, "
# define COMMDS_NB2			"the command will have no effect."
# define COMMDS_AVAILABLE	"available commands"
# define ANTS_NAME			"number of ants"
# define ANTS_DESCRIPTION	"strictly positive value"
# define ANTS_PLACEMENT		"at the top of the file"
# define ANTS_EX			"Example: 16"
# define ROOM_NAME			"rooms"
# define ROOM_DESCRIPTION	"room name followed by two integer coordinates"
# define ROOM_PLACEMENT		"after ant number, before tubes information"
# define ROOM_EX			"room_Name 5 4"
# define ROOM_NB1			"a room name cannot start with L or #"
# define ROOM_NB2			"forbidden character: -"
# define TUBE_NAME			"tubes"
# define TUBE_DESCRIPTION	"link between two existing rooms"
# define TUBE_PLACEMENT		"after rooms"
# define TUBE_FORWARD		"forward direction: ->"
# define TUBE_BACKWARD		"backward direction: <-"
# define TUBE_ANYWAY		"any direction: - or <->"
# define TUBE_EX			"room1-other_room"

typedef struct			s_point
{
	int					value;
	int					len;
}						t_point;

typedef struct			s_node
{
	int					value;
	int					previous;
	int					color;
	int					parent;
}						t_node;

typedef struct			s_file
{
	int					begin;
	int					end;
	int					*tab;
}						t_file;

typedef struct			s_graphe
{
	unsigned int		nb_rooms;
	unsigned int		nb_tubes;
	t_node				**node;
	int					*color;
	int					*previous;
	char				**map;
	int					**graph;
	int					*capacite;
	int					start;
	int					end;
	int					nb_paths;
	int					start_next_to_end;
	t_file				*file;
}						t_graphe;

typedef struct			s_room
{
	char				*name;
	t_4vect				pos;
}						t_room;

typedef struct			s_input
{
	int 				nb_ants;
	t_room				*room;
	int					**commands;
	int					nb_commands;
}						t_input;

typedef struct			s_tab
{
	int					*tab;
	int					length;
}						t_tab;

typedef struct			s_environment
{
	t_list				*anthill;
	t_input				*ins;
	t_graphe			*graphe;
	t_tab ***			all_paths;
	int					**ants;
	int					nb_paths;
	int					options;
	int					type;
	int					turns;
	int					nb_line;
	int					fd;
	int					arrived_turn;
	int					max_paths;
}						t_environment;

enum					e_error
{
	NO_ERR, ERR_NO_INS, ERR_ANT_NB, ERR_NOTUBE, ERR_START, ERR_END, ERR_SAME,
	ERR_LIB, ERR_ALLOC, ERR_ARG, ERR_SOLUTION,
	NO_WRNG, WRNG_ANT_INPUT, WRNG_INTMAX, WRNG_INTMIN, WRNG_ROOM,
	WRNG_ROOM_CONF, WRNG_DUP, WRNG_ROOM_CHAR, WRNG_COORD, WRNG_TUBE_NOROOM,
	WRNG_TUBE, WRNG_INPUT, WRNG_HELP, WRNG_OPTION, WRNG_FAILED_START,
	WRNG_FAILED_END, WRNG_DOUBLE_START, WRNG_DOUBLE_END, WRNG_SAME_ROOM,
};

enum					e_type
{
	TYPE, NUMBER, ANTS, ROOM, TUBE, COMMENT, COMMAND
};

enum					e_direction
{
	FORWARD, BACKWARD, BOTH
};

enum				e_display
{
	DISPLAY_OFF, DISPLAY_ON
};

void			getleaks(char *str);

/*
** DISPLAY
*/

void			display_anthill(ENV *e);
void			display_help(ENV *e);
int				display_error(ENV *e, int code);
void			display_moves(ENV *e, int **tab, int total);
void			display_turns(ENV *e);
int				display_warning(ENV *e, int code);
int				display_travelling(ENV *e, int display);
char			*get_errmsg(int code);

/*
** INITIALIZE, CLEAN AND FREE
*/

void			clean_node(t_graphe *g);
t_file			*clean_file(t_file *file, int size);
t_node			*create_node(int value);
int				**create_double_int_tab(int taille, int val);
int				*create_tab(int taille, int val);
t_tab			***create_besttab(int nbpath);
void			free_graphe(t_graphe *g);
void			free_env(ENV *e);
t_file			*new_file(t_graphe *g);
int				set_env(ENV *e);

/*
** SCAN PATHS
*/
int				ant_enter_path(ENV *e, int comb);
void			move_next_room(ENV *e);

/*
** READ AND PARSE
*/

int			apply_commands(ENV *e);
int			get_ants(ENV *e, char **str, int type);
int			get_command(ENV *e, char *str, int option);
int			get_room(ENV *e, char **str);
int			get_tube(ENV *e, char **str, int way, int len);
void		link_command(ENV *e, int type, int index);
int			read_instructions(ENV *e, char *str);
int			read_options(ENV *e, char **argv, int argc);
//char		**room_names(t_list *l, int nb_rooms, int **paths, int nb_paths);
int			setup_room_mtrx(ENV *e, int size);
int			store_rooms(ENV *e);

/*
** SOLVE
*/
int				addfile(t_file *file, int value);
int				convert_graphe(t_graphe *g);
int				find_best_solution(t_graphe *g, ENV *e);
int				*prediction(ENV *e, t_graphe *g);
int				removefile(t_file *file);
t_tab			***register_path(t_graphe *g, int nbpath, t_tab ***besttab);
int				scan_allmoves(ENV *e, int display);
int				sort_path(t_graphe *g);
int				try_to_place_ant(t_tab ***besttab, int *tab_fourmis);

#endif
