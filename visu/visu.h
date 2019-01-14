/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:49:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 17:07:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VISU_H
# define VISU_H

#include "libft.h"
#include "mlx.h"
#include "X.h"

# define ENV			t_environment
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define ERR_NB			21
# define NB_COMMANDS		2
# define SPEED			50

/*
** NICE COLORS
*/
# define BBLACK			0x000000
# define RED			0xEF5350
# define PINK			0xEC407A
# define PURPLE			0x7E57C2
# define INDIGO			0x5C6BC0
# define BLUE			0x42A5F5
# define LBLUE			0x29B6F6
# define CYAN			0x26C6DA
# define TEAL			0x26A69A
# define GREEN			0x66BB6A
# define LGREEN			0x9CCC65
# define LIME			0xD4E157
# define YELLOW			0xFFEE58
# define AMBER			0xFFCA28
# define ORANGE			0xFFA726
# define DORANGE		0xFF7043
# define BROWN			0x8D6E63
# define BGREY			0x78909C



# define COL_ROOM		TEAL
# define COL_TUBES		TEAL
# define COL_ANT		RED
# define COL_ANTNAME	AMBER


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

# define VISU 			t_visu
# define SCREEN_W 2600
# define SCREEN_H 1440
# define TRANS		7
# define WIN_W		1200
# define WIN_H		1200
# define PADDING	100
# define MAX_Y			2 //changer
# define MAX_X			1 //changer
# define MIN_W			1000	//changer
# define MIN_H			1000	//changer
# define WIN_TITLE		"VISU LEM_IN"
# define PPMOVE_RATIO	0.00001

# define KEY_ESC		53
# define KEY_LF			123
# define KEY_RT			124
# define KEY_UP			126
# define KEY_DW			125
# define KEY_XUP		91
# define KEY_XDW		84
# define KEY_YUP		86
# define KEY_YDW		88
# define KEY_ZUP		92
# define KEY_ZDW		89
# define KEY_ZMIN		69
# define KEY_ZMOUT		78
# define KEY_DEFAULT	15
# define KEY_INVERT		34
# define KEY_PAUSE		49
# define KEY_FASTER		116
# define KEY_SLOWER		121

/*
# define KEY_ESC		65307
# define KEY_LF			65361
# define KEY_RT			65363
# define KEY_UP			65362
# define KEY_DW			65364
# define KEY_XUP		65431
# define KEY_XDW		65433
# define KEY_YUP		65430
# define KEY_YDW		65432
# define KEY_ZMIN		65451
# define KEY_ZMOUT		65453
# define KEY_DEFAULT	15
# define KEY_PAUSE		65429
*/
# define MLX		"failed setting up mlx"


enum		e_errors
{
	NO_VISU_ERR, ERR_MLX
};

enum		e_coord
{
	X, Y
};


enum					e_type
{
	ANTS, ROOM, TUBE, COMMENT, COMMAND
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


enum				e_angle
{
		COSX, SINX, COSY, SINY, COSZ, SINZ
};

enum				e_room
{

		CURRENT, NEXT
};

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

typedef struct			s_image
{
	int					size;
	int					bpp;
	int					endian;
	void				*img;
	char				*ptr;
}						t_image;



typedef struct			s_uservar
{
	double				event_m[4][4];
	double				rotx;
	double				roty;
	double				zoom;
	double				height;
	int					mv_hor;
	int					mv_ver;
	int					invert;
	int					rotcolor;
	int					color;
	int					color_map;
	int					vegas;
}						t_uservar;

typedef struct			s_linecoord
{
	int					x0;
	int					y0;
	int					z0;
	int					x1;
	int					y1;
	int					z1;
	int					dx;
	int					dy;
}						t_linecoord;

typedef struct s_visu
{
	void		*mlx;
	void		*win;
	int			*map;
	t_image		img;
	t_4vect		shift;
	t_4vect		min;
	t_4vect		max;
	t_linecoord	coord;
	t_uservar	uinput;
	t_input			*ins;
	t_graphe		*graphe;
	t_list		*anthill;
	char		turn_str[11];
	int		**ants;
	int			nb_paths;
	int			options;
	int			type;
	int			fd;
	int			mesh_init;
	int			mesh_size;
	int			width;
	int			height;
	int			win_w;
	int			win_h;
	int			ppmove;
	int			revert;
	int			maxzoomin;
	int			maxzoomout;
	int			setextremes;
	int			color;
	double		coef;
	int			center;
	int			pause;
	int			step;
	int			turn;
	t_4fvect		delta;
	double		speed;

}				t_visu;

/*
** DISPLAY
*/

void		display_rooms(VISU *v);
void		display_everything(VISU *v);

/*
** ENV
*/
void		set_visu(VISU *v);
void		free_graphe(t_graphe *g);

/*
** USER ACTION
*/
int		ft_dealkey(int key, VISU *v);
void	ft_transform_points(VISU *v);


/*
 ** IMAGE
 */
int		ft_get_img(VISU *v);
void	ft_put_to_img(VISU *v, int row, int col, int color);
void	ft_points_to_img(VISU *v);

/*
 ** WINDOW
 */
int		ft_init_win(VISU *v);
int		ft_close_window(VISU *v);

/*
 ** PLOT
 */
void	ft_drawline(VISU *v);

/*
 ** MATRICES
 */
void	ft_getm_center_to_origin(VISU *v, double (*dest)[4][4]);
void	ft_getm_setcenter(VISU *v, double (*dest)[4][4]);
void	ft_getm_rot(VISU *v, double (*dest)[4][4]);
void	ft_getm_zoom(VISU *v, double (*dest)[4][4]);
void	ft_getm_scaleup(VISU *v, double (*dest)[4][4]);
void	ft_getm_scaledown(VISU *v, double (*dest)[4][4]);
void	ft_getm_trans(VISU *v, double (*dest)[4][4]);
void	ft_getm_move(VISU *v, double (*dest)[4][4]);

int			set_env(VISU *v);
void			free_env(VISU *v);
void			free_strtab(char ***tab);
void			del_anthill(t_list *l);
char			*get_errmsg(int code);

int			is_dup(VISU *v, char *str, int max_index);

void		display_adj_mtrx(int **tab, int size);
void		print_rooms(VISU *v, char **rooms);

void		ft_get_meshsize(VISU *v);

/*
 * ** Display
 * */

int			display(VISU *v, char *str);
void		display_ant(VISU *v, int *ant, int scale);
void		display_anthill(t_list *anthill);
void		printlist(VISU *v, t_list *l);
void		display_ants(VISU *v, int x, int y, int scale);


int			read_options(VISU *v, char **argv, int argc);
int		display_moves(VISU *v, int color, int option);
int			anim_moves(VISU* v);
void		display_square(VISU *v, int *ant, int width, int color);

void		display_ant_names(VISU *v);

void		detect_end(VISU *v);

/*
 * ** Read and store instructions
 * */
int			read_moves(VISU *v, char *line, int room);
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
int		get_room_index(VISU *v, char *name, int len);

/*
 * ** Utils
 * */

int			is_number(char *str);

# endif
