/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:36:04 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:44:42 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		initialisation_liste_opt est une fonction qui cree une liste d'option
**		et qui la remplie de fonction
**		option contient
**			_une cle (keyword)
**			_un enum contenant tout les type
**			une union qui contien une fonciton
*/

void		ft_clean_option(t_option *opt)
{
	t_option *tmp;

	while (opt != NULL)
	{
		tmp = opt;
		opt = opt->next;
		free(tmp);
	}
}

t_option	*ft_opt_long_long_int(t_option *l, const char *kw,
		int (*f)(long long, t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptLongInt;
	li->fct.opt_long_long_int = f;
	li->next = l;
	return (li);
}

t_option	*initialisation_liste_opt(void)
{
	t_option	*opt;

	opt = (t_option*)NULL;
	opt = ft_opt_w_char(opt, "wchar", ft_put_unicode);
	opt = ft_opt_void(opt, "void", ft_put_void);
	opt = ft_opt_long_long_int(opt, "signed", ft_put_longlongint);
	opt = ft_opt_string(opt, "string", ft_put_string);
	opt = ft_opt_w_string(opt, "wstring", ft_put_unicode_string);
	opt = ft_opt_base(opt, "base", ft_put_base);
	opt = ft_opt_adress(opt, "address", ft_put_address);
	opt = ft_opt_unsigned_long_long_int(opt, "unsigned",
	ft_put_unsignedlonglongint);
	return (opt);
}
