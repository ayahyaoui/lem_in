/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 22:35:44 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/06 06:48:58 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_div
{
	int				quot;
	int				rem;
}					t_div;

typedef struct		s_gnl
{
	char			*str;
	int				fd;
	int				len;
	int				empty;
	struct s_gnl	*next;
	struct s_gnl	*prec;
}					t_gnl;

int					get_next_line(const int fd, char **l);

void				*ft_realloc(char *l, int t);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c,
					size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strfreecat(char *s, char *str);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
char				*ft_strstr(const char *big, const char *little);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_lstdelone(t_list **alst, void (*del) (void*, size_t));
void				ft_lstdel(t_list **alst, void (*del) (void*, size_t));
void				ft_lstadd(t_list **alst, t_list *news);
void				ft_lstiter(t_list *lst, void(*f) (t_list *elem));
t_list				*ft_lstnew(void const *content, size_t size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem));

t_list				*ft_lstrev(t_list *l);
void				ft_printbit(int val);
void				ft_printbit_rev(int val);
int					ft_printnbit(int val, int max);
int					ft_printnbit_rev(int val, int max);
unsigned long long	ft_power2(unsigned int val);
char				*ft_itoa_base(long long nb, int base);
char				*ft_itoa_base2(long long nb, int base, int nb_oct, int maj);
size_t				ft_lennbr_base(long long nb, int b);
size_t				ft_lenbase(long long nb, size_t b);
int					ft_strrev(char *str);
char				*ft_strcjoin(char const *s1, char const *s2, char c);
int					ft_isspace(int c);
char				*ft_strmerge(char **str);
int					ft_affichetab(int *tab, int size, char c);
void				ft_swap(int *a, int *b);
int					ft_sortinttab(int *tab, int size);
void				ft_printbase(int nb, size_t base);
long long			ft_atol(char *str);
int					ft_abs(int i);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_issort(int *tab, int s);
int					ft_isinteger(char *str);
void				ft_tri_fusion_iterative(int *tab, int len);
int					*ft_tri_fusion_recursive(int *tab, int len);
t_div				ft_div(int num, int denominateur);
size_t				ft_lenbase2(long long nb, size_t b, int size);
int					log2_simp(int n);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
unsigned int		ft_logarithme2(unsigned int nb);
void				ft_del_dim2(char **str, int len);
size_t				ft_strlen_dim2(char **str);
void				ft_affiche_string_dim2(char **str, int ac);
char				*ft_strcmerge(char **str, char c);
int					ft_isintab(int *tab, int len, int value);
#endif
