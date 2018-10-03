/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 00:03:45 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/23 23:49:39 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

# define BUFF_SIZE 1024

typedef struct		s_printf
{
	int				larg;
	int				precis;
	enum
	{
		PLUS = 1,
		SPACE
	}				flag_1;
	enum
	{
		MOINS = 1,
		ZERO
	}				flag_2;
	int				flag_3;
	int				maj;
}					t_printf;

typedef enum		e_spec
{
	OptVoid = 1,
	OptString,
	OptWString,
	OptAddress,
	OptBase,
	OptLongChar,
	OptChar,
	OptWChar,
	OptShortShortInt = 10000 + 100 - 2,
	OptShortInt,
	OptInt,
	OptLongInt,
	OptLongLongInt,
	OptIntMax = 10000 + 100 + 2,
	OptHexa = 10000 + 160,
	OptOctal = 10000 + 80,
	OptUnsignedShortShortInt = 10000 + 200 - 2,
	OptUnsignedShortInt,
	OptUnsignedInt,
	OptUnsignedLongInt,
	OptUnsignedLongLongInt,
	OptUnsignedIntMax = OptUnsignedLongLongInt,
}					t_spec;

typedef union		u_fct
{
	int		(*opt_void)(t_printf);
	int		(*opt_long_long_int)(long long, t_printf);
	int		(*opt_unsigned_long_long_int)(unsigned long long, t_printf);
	int		(*opt_w_char)(int, t_printf, int t);
	int		(*opt_w_str)(int*, t_printf);
	int		(*opt_str)(const char*, t_printf);
	int		(*opt_base)(long long, t_printf, int size, int base);
	int		(*opt_address)(void*, t_printf);
}					t_fct;

typedef struct		s_option
{
	const char		*keyword;
	struct s_option	*next;
	t_spec			spec;
	t_fct			fct;
}					t_option;

int					ft_printf(const char *str, ...);

t_option			*initialisation_liste_opt();
t_option			*ft_opt_void(t_option *l, const char *kw,
					int (*f)(t_printf));
t_option			*ft_opt_w_char(t_option *l, const char *kw,
		int			(*f)(int, t_printf, int t));
t_option			*ft_opt_w_string(t_option *l, const char *kw,
		int			(*f)(int*, t_printf));
t_option			*ft_opt_string(t_option *l, const char *kw,
		int			(*f)(const char*, t_printf));
t_option			*ft_opt_long_long_int(t_option *l, const char *kw,
		int			(*f)(long long, t_printf));
t_option			*ft_opt_unsigned_long_long_int(t_option *l, const char *kw,
		int			(*f)(unsigned long long, t_printf));
t_option			*ft_opt_base(t_option *l, const char *kw,
		int			(*f)(long long, t_printf, int, int));
t_option			*ft_opt_adress(t_option *l, const char *kw,
		int			(*f)(void*, t_printf));

int					ft_parsing(t_option *l, char *str, va_list va);
int					ft_parsingbis(t_option *cursor, char *str,
					va_list va, char *buff);
int					ft_process_param(t_option *cursor, char *str,
					va_list va, int *res);

int					ft_spe(char *s);
int					ft_secure(char *str);
t_printf			init_pr();
char				*get_key(int spe);
int					ft_isflag(char c);
t_printf			ajout_flag(char c, t_printf pr);
t_printf			get_flag(t_printf p, char *str);
int					ft_spe2(char *str);
int					ft_spe_base(char *str, int l);
int					ft_spe_type(char c);
int					ft_istype(char c);
int					ft_isspec(char c);

int					ft_put_unicode(wchar_t c, t_printf pr, int t);
int					ft_put_unichar(wchar_t c, int taille);
int					ft_get_unichar(char *tab, wchar_t c, int taille);
int					ft_put_unicode_string(wchar_t *str, t_printf pr);
int					ft_put_null_string(t_printf pr);
int					len_unicode_byte(wchar_t w);
int					ft_put_string(const char *x, t_printf pr);
int					ft_putstr_null(t_printf pr, int spe);

int					ft_put_address(void *ptr, t_printf pr);

char				*ft_put_base2(t_printf pr, int t2, int base, int t);
int					ft_put_base(long long x, t_printf pr, int size, int base);
int					ft_put_octal(long long x, t_printf pr, int size);
int					ft_put_hexa(long long x, t_printf pr, int s);

void				ft_put_longlongint_larg(long long x, t_printf pr,
					int t, int type);
void				ft_longlongnbr(char *res, long long x, size_t t);
size_t				taille_unsignedlonglongnbr(unsigned long long x, size_t t,
					t_printf pr);
void				ft_unsignedlonglongnbr(char *res, unsigned long long x,
					size_t t);
size_t				taille_longlongnbr(long long x, size_t t, t_printf pr);
void				ft_longlong(char *res, long long x, size_t t, int type);
void				ft_longlongnbr(char *res, long long x, size_t t);
int					ft_put_longlongint(long long x, t_printf pr);
int					ft_put_unsignedlonglongint(unsigned long long x,
					t_printf pr);

void				ft_put_space(long long x, t_printf pr, int size, int base);

int					ft_put_void(t_printf pr);

void				ft_clean_option(t_option *opt);

void				undefined(char *where, int i, char *ou, char *msg);
void				affiche_info(t_printf pr, int spe);

#endif
