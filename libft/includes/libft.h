/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:08:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 02:02:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef	struct	s_4vect
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_4vect;

typedef	struct	s_4fvect
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_4fvect;

typedef struct	s_4ivect
{
	int		x;
	int		y;
	int		z;
	int		w;
}				t_4ivect;

/*
** Chars
*/
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
** Conversion
*/
int				ft_atoi(const char *str);
int				ft_atoi_index(unsigned char *str, int *count);
char			*ft_itoa(int n);
char			*ft_uitoa(unsigned int n);
char			*ft_lltoa(long long n);

/*
** Lists
*/
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddcircle(t_list **alst, t_list *new);
void			ft_lstaddend(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void(*del)(void*, size_t));
void			ft_lstdelone(t_list **alst, void(*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstnewf(void const *content, size_t content_size);
int				ft_lstsize(t_list *lst);

/*
** Memory
*/
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *str, int c, size_t len);

/*
** Output
*/
int				ft_display_error(char *msg);
void			ft_mdisplay(double (*m)[4][4]);
int				ft_printf(const char *format, ...);
void			ft_print_inttab(int *tab, int len);
void			ft_printstrarr(char **arr);
void			ft_putchar(int c);
void			ft_putchar_fd(int c, int fd);
void			ft_putcnl(char c);
void			ft_putendl(char *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putendl_uns(unsigned char *s);
void			ft_putnbr(int n);
void			ft_putnbrnl(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char *str);
void			ft_putstr_fd(char const *s, int fd);

/*
** Numbers
*/
size_t			ft_abs(int n);
unsigned int	ft_base_to_deci(unsigned int num, int base);
int				ft_beyond_limiti(char *str);
double			ft_dabs(double num);
double			ft_dsqrt(double num);
size_t			ft_endien_btl(size_t valbe);
float			ft_fabs(float num);
long long		ft_llabs(long long n);
size_t			ft_lllen(long long n);
long long		ft_llpow(long long n, int pow);
int				ft_maxint(int a, int b);
size_t			ft_nblen(int n, int base);
size_t			ft_nbwords(char *str, int sep, int i);
int				ft_pow(int n, int pow);
void			ft_sort_int_tab(int *tab, size_t size);
int				ft_strarrlen(char **str);
void			ft_swap(int *a, int *b);
void			ft_swapd(double *a, double *b);

/*
** Strings
*/
int				get_next_line(const int fd, char **line);
int				get_next_line2(const int fd, char **line);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strchri(const char *s, int c, int i);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
int				ft_strcstr(char *str, char *chars);
void			ft_strdel(char **as);
char			*ft_strdup(const char *str);
char			*ft_strdupf(char *dest, const char *str, int to_free);
int				ft_strequ(const char *s1, const char *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinf(char *s1, char *s2, int to_free);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(char *str);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strnbc(char *str, char c);
int				ft_strnbci(char const *s, char c, int i);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(char const *s, unsigned int beg, size_t len);
char			*ft_strsubf(char const *s, unsigned int beg,
				size_t len, char *to_free);
char			*ft_strtrim(char const *s);

/*
** Vectors & matrices
*/
void			ft_44maddd(double (*m)[4][4], double val);
void			ft_44maddrows(double (*m)[4][4], int row_dest, int row_add);
void			ft_44mcpy(double (*dest)[4][4], double (src)[4][4]);
void			ft_44minit(double (*m)[4][4], int val);
void			ft_44mrow_addd(double (*m)[4][4], int row, double val);
void			ft_44mswap_rows(double (*m)[4][4], int r1, int r2);
void			ft_44mtrxmtrx_mul(double (*dest)[4][4],
				double m1[4][4], double m2[4][4]);
void			ft_44mtranspose(double (*m)[4][4]);
void			ft_4fvinit(t_4fvect *v, float x, float y, float z);
void			ft_4fvcpy(t_4fvect *dest, t_4fvect src);
void			ft_4ivinit(t_4ivect *v, int x, int y, int z);
void			ft_4ivcpy(t_4ivect *dest, t_4ivect src);
t_4vect			ft_4mtrxvect_mul(double (*m)[4][4], t_4vect *ver);
void			ft_4vcpy(t_4vect *dest, t_4vect src);
double			ft_4vectvect_mul(t_4vect hor, t_4vect ver);
void			ft_4vinit(t_4vect *v, double x, double y, double z);
t_4vect			ft_get4mcol(double m[4][4], int col);
t_4vect			ft_get4mrow(double m[4][4], int row);
double			ft_getmval(double m[4][4], int row, int col);
void			ft_swap4v(t_4vect *v1, t_4vect *v2);

#endif
