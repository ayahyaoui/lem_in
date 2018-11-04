/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:09 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 01:41:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN__
#define __LEMIN__

#include "libft.h"

# define ENV			t_environment
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define ERR_NB			18
# define NB_COMMANDS	2

# define SPLIT			"error strsplit" // remplacer par erreur + generique
# define NOINS			"empty file"
# define ANT_INPUT		"invalid ant format"
# define ANT_NB			"not enough ants!"
# define ROOM_INPUT		"invalid room format"
# define ROOM_DUP		"duplicate room name"
# define COORD			"non numerical values as room coordinates"
# define TUBE_INPUT		"invalid tube input"
# define TUBE_NOROOM	 "linking non-nexistant room"
# define ORDER			"invalid input order"
# define HELP			"(-h for usage)"
# define LIB			"failing lib function"
# define MALLOC			"failing malloc"
# define NOSTART		"missing start indicator"
# define NOEND			"missing end indicator"
# define ROOM_CONF		"confusing room name, please avoid use of '-'"
# define MAXINT			"max number is 2 147 483 647"


typedef struct		s_graphe
{
	int				nb_rooms; // anciennement taille
	int				nb_tubes;
	int				**map;
	int				start;
	int				end;
}					t_graphe;

typedef struct		s_special
{
	int				status;
	int				index;
	int				dest[2];
	char			*str;
}					t_special;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
}					t_room;

typedef struct 		s_input
{
	int 			nb_ants;
	t_graphe 		*links;
	char			**room;
	t_list	 		*rooms;
	t_list			*special;
}					t_input;

typedef struct		s_environment
{
	t_list			*anthill;
	t_input			*ins;
	t_graphe		*graphe;
	int			nb_paths;
	int				options;
	int				type;
	int				fd;
}					t_environment;

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


enum				e_error
{
	NO_ERR, ERR_NO_INS, ERR_READ, ERR_ANT_INPUT, ERR_ANT_NB, ERR_INTMAX,
   	ERR_ROOM, ERR_ROOM_CONF, ERR_COORD, ERR_TUBE, ERR_NOROOM, ERR_DUP, ERR_ORDER,
	ERR_START, ERR_END, ERR_LIB, ERR_ALLOC, ERR_HELP 
};

int			set_env(ENV *e);
void			free_strtab(char ***tab);
void			del_rooms(t_list *l);
char			*get_errmsg(int code);


//TEMP
void		display_adj_mtrx(int **tab, int size);



/*
** Display
*/

int			display(ENV *e, char *str);
void		display_moves(ENV *e, int **tab, char **names, int total);
void		display_anthill(t_list *anthill);
void		printlist(ENV *e, t_list *l);

/*
** Read and store instructions
*/

void		apply_commands(ENV *e);
int			get_ants(ENV *e, char **str, int type);
int			get_command(ENV *e, char *str);
int			get_room(ENV *e, char **str);
int			get_tube(ENV *e, char **str, int endrooms);
void			link_command(ENV *e, int type, int index);
int			read_instructions(ENV *e, char *str, int nbline, int ret);
char		sep(char *line, int *type);
char		**room_names(t_list *l, int nb_rooms, int **paths, int nb_paths);

/*
** Utils
*/

int			is_number(char *str);

#endif
