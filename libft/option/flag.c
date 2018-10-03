/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:23:03 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:35:02 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		flag contient quelque fonction sur les flag
**		get_flag recupere :
**			pr : qui peu contenir diffrente info sur ce que l'on va afficher
**			str: String contenant l'elment
**		et ajoute tout les flag
*/

char		*get_key(int spe)
{
	if (spe == 0)
		return (NULL);
	if (spe == OptVoid)
		return (ft_strdup("void"));
	if (spe >= 10098 && spe <= 10102)
		return (ft_strdup("signed"));
	if (spe >= 10198 && spe <= 10202)
		return (ft_strdup("unsigned"));
	if (spe == OptString)
		return (ft_strdup("string"));
	if (spe == OptWString)
		return (ft_strdup("wstring"));
	if (spe == OptChar || spe == OptWChar)
		return (ft_strdup("wchar"));
	if (spe == OptAddress)
		return (ft_strdup("address"));
	if ((spe >= 10158 && spe <= 10162) || (spe >= 10078 && spe <= 10082))
		return (ft_strdup("base"));
	undefined("get_key", -1, "impossible", "aucune spe trouve");
	return (NULL);
}

int			ft_isflag(char c)
{
	if (c == ' ' || c == '-' || c == '+' || c == '#' ||
	c == '0')
		return (1);
	return (0);
}

t_printf	ajout_flag(char c, t_printf pr)
{
	if (c == '+')
		pr.flag_1 = PLUS;
	if (c == ' ' && pr.flag_1 == 0)
		pr.flag_1 = SPACE;
	if (c == '-')
		pr.flag_2 = MOINS;
	if (c == '0' && pr.flag_2 == 0)
		pr.flag_2 = ZERO;
	if (c == '#')
		pr.flag_3 = 1;
	return (pr);
}

t_printf	get_flag(t_printf pr, char *str)
{
	int i;

	i = -1;
	while (ft_isflag(str[++i]) == 1)
		pr = ajout_flag(str[i], pr);
	pr.larg = (ft_isdigit(str[i]) == 1) ? ft_atoi(&str[i]) : pr.larg;
	while (ft_isdigit(str[i]) == 1)
		i++;
	if (str[i + 1] && str[i] == '.' && (ft_isdigit(str[i + 1]) ||
				(ft_istype(str[i + 1]) == 1 || ft_isspec(str[i + 1]) == 1)))
	{
		pr.precis = ft_atoi(&str[++i]);
		while (ft_isdigit(str[i]) == 1)
			i++;
	}
	while (str[i] && ft_isspec(str[i]))
		i++;
	pr.flag_2 = (pr.flag_2 == ZERO && pr.precis != -1 && str[i] != '%')
		? 0 : pr.flag_2;
	if (ft_istype(str[i]) && ft_isupper(str[i]))
		pr.maj = 1;
	if (ft_istype(str[i]) == 1 || ft_isspec(str[i]) == 1)
		return (pr);
	undefined("get_flag", i, str, "Probleme sur les flag");
	return (pr);
}
