/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:27:08 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/21 17:37:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <inttypes.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>

# define BUFF_SIZE 200
# define CONV_TAB (*tab[])(t_env *env, char *format, va_list ap)

union			u_type
{
	unsigned long long int	ulli;
	int						i;
	char					c;
	wchar_t					wc;
	wchar_t					*wcs;
	unsigned char			uc;
	unsigned int			ui;
	short int				si;
	long int				li;
	long unsigned int		uli;
	long long int			lli;
	float					f;
	double					d;
	unsigned char			*s;
	intmax_t				maxi;
	uintmax_t				umaxi;
	size_t					zi;
};

typedef struct	s_env
{
	int				field;
	int				prec;
	int				mod;
	char			id;
	unsigned char	tmpbuf[BUFF_SIZE];
	unsigned char	buf[BUFF_SIZE];
	unsigned char	*str;
	unsigned char	wbuf[BUFF_SIZE];
	unsigned char	wtmp[5];
	int				index;
	union u_type	arg;
	int				base;
	int				len;
	int				mask_len;
	int				error;
	int				i;
	int				j;
	int				k;
	int				fill_field;
	int				fill_prec;
	int				neg;
	unsigned char	flags;
	int				specs;
	int				err_ind;
	int				output;
	int				nullarg;
	int				color_chars;
	int				r;
	int				pindex;
	int				rindex;
	int				prev;
	int				cc;
}				t_env;

enum			e_modificateurs
{
	NOMOD, H, HH, L, LL, Z, J
};

enum			e_flags
{
	POUND, ZERO, MINUS, SPACE, PLUS
};

void			ft_putendl(char *str);
int				ft_printf(const char *format, ...);

/*
 ** Initialize & Clear
*/
void			ft_setzero(unsigned char str[], int len, char c);
int				ft_clear_form(t_env *env);
void			ft_init_fttab(void
				(*tab_conv[128])(t_env *env, char *s, va_list ap));
/*
** Parse
*/
int				ft_read_until_arg(t_env *env, unsigned char **s2, va_list ap);
int				ft_read_specs(t_env *env, char **str);

/*
** Read argument
*/
void			ft_inthh(t_env *env, va_list ap);
void			ft_inth(t_env *env, va_list ap);
void			ft_intllz(t_env *env, va_list ap);
void			ft_intl(t_env *env, va_list ap);
void			ft_intj(t_env *env, va_list ap);
void			ft_unshh(t_env *env, va_list ap);
void			ft_unsh(t_env *env, va_list ap);
void			ft_unsl(t_env *env, va_list ap);
void			ft_unsll(t_env *env, va_list ap);
void			ft_unsj(t_env *env, va_list ap);
void			ft_unsz(t_env *env, va_list ap);
void			ft_intnone(t_env *env, va_list ap);
void			ft_unsnone(t_env *env, va_list ap);

/*
 ** Convert to string
*/
void			ft_ultoa_base_cust(t_env *env,
				unsigned char *str, unsigned long int num);
void			ft_ulltoa_base_cust(t_env *env,
				unsigned char *str, unsigned long long num);
void			ft_lltoa_base_cust(t_env *env,
				unsigned char *str, long long int num);
void			ft_uitoa_base_cust(t_env *env,
				unsigned char *str, unsigned int num);
void			ft_ltoa_base_cust(t_env *env,
				unsigned char *str, long int num);
void			ft_itoa_base_cust(t_env *env,
				unsigned char *str, int num);
void			ft_ftoa_base_cust(t_env *env,
				unsigned char *str, double num);
unsigned int	ft_putwchar(t_env *env, int n);

/*
 ** Add to buffer
*/
void			ft_addsign_wzero(t_env *env);
void			ft_addsign_nozero(t_env *env);
void			ft_addtobuf(t_env *env, char c, int times);
void			ft_addtobuf_field(t_env *env, char c, int times);
void			ft_addtobuf_prec(t_env *env, char c, int times);
void			ft_addtobuf_switch(t_env *env, int times);
void			ft_add_prefix_hex(t_env *env);
void			ft_add_prefix_oct(t_env *env);
void			ft_add_prefix_uns(t_env *env);
void			ft_add_prefix_ptr(t_env *env);
void			ft_strcpyi_buf(t_env *env, unsigned char src[], int *index);
void			ft_strncpyi_buf(
				t_env *env, unsigned char src[], int *index, int n);
void			ft_strncpyi_wbuf(
				t_env *env, unsigned char src[], int *index, int n);
void			ft_strncpyi_tmp(
				t_env *env, unsigned char src[], int *index, int n);
/*
** Apply conversion specifications
*/
void			mng_nullarg(t_env *env);
void			ft_apply_specs_int(t_env *env);
void			ft_apply_specs_hex(t_env *env);
void			ft_apply_specs_oct(t_env *env);
void			ft_apply_specs_uns(t_env *env);
void			ft_apply_specs_ptr(t_env *env);
void			ft_apply_specs_float(t_env *env);
void			ft_apply_specs_char(t_env *env);
void			ft_apply_specs_str(t_env *env);
void			ft_apply_specs_wcs(t_env *env);

/*
** Conversions
*/
void			ft_bigd(t_env *env, char *format, va_list ap);
void			ft_bigo(t_env *env, char *format, va_list ap);
void			ft_bigu(t_env *env, char *format, va_list ap);
void			ft_p(t_env *env, char *format, va_list ap);
void			ft_d(t_env *env, char *format, va_list ap);
void			ft_i(t_env *env, char *format, va_list ap);
void			ft_o(t_env *env, char *format, va_list ap);
void			ft_u(t_env *env, char *format, va_list ap);
void			ft_x(t_env *env, char *format, va_list ap);
void			ft_bigx(t_env *env, char *format, va_list ap);
void			ft_c(t_env *env, char *format, va_list ap);
void			ft_bigc(t_env *env, char *format, va_list ap);
void			ft_s(t_env *env, char *format, va_list ap);
void			ft_bigs(t_env *env, char *format, va_list ap);
void			ft_noconv(t_env *env, char *format, va_list ap);
void			ft_e(t_env *env, char *format, va_list ap);
void			ft_b(t_env *env, char *format, va_list ap);
void			ft_n(t_env *env, char *format, va_list ap);

/*
** Bonus
*/
int				ft_reset_color(t_env *env);
int				ft_check_color(t_env *env, char *str, va_list ap);
void			ft_printbit(t_env *env, unsigned int n, int size);

/*
 ** Support functions
*/
void			ft_mng_flags(t_env *env);
int				ft_is_mod(unsigned char c);
int				ft_is_flag(unsigned char c);
void			ft_strcapitalize(unsigned char *str);
void			ft_mng_negative_arg(t_env *env, long long int *num);
int				ft_fnblen(double num);
int				ft_unblen(unsigned int num, int base);
int				ft_llnblen(long long num, int base);
int				ft_ullnblen(unsigned long long num, int base);
size_t			ftp_strlen(char *str);
int				ftp_toupper(int c);
int				ftp_isdigit(int c);
int				ftp_isalpha(int c);
int				ftp_strequ(const char *s1, const char *s2);
int				ftp_strnequ(const char *s1, const char *s2, size_t n);
int				ftp_abs(int n);
int				ftp_nblen(int n, int base);
int				ftp_maxint(int a, int b);
int				ftp_strcstr(char *str, char *chars);
int				ftp_strcmp(const char *s1, const char *s2);
int				ftp_strncmp(const char *s1, const char *s2, size_t n);

#endif
