/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:45:54 by anyahyao          #+#    #+#             */
/*   Updated: 2018/04/06 20:31:56 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include <stdio.h>

FILE *fd;

int main(int ac, char **av)
{
	t_pile		*p,*p2;
	int			i;
	t_tab		*t;

	fd = fopen("result.txt","w+");
	if (ac == 1)
		return (0);
	i = ac - 1;
	p = ft_pilenew(atoi(av[ac - 1]));
	while (--i > 0)
		p = ft_piladd(p,atoi(av[i]));
	p2 = ft_pilenew(0);
	remove_head(p2);
	t = malloc(sizeof(t_tab));
	t->tab = convert_tab(p);
	t->size = p->nb_elem;
	//regle("aff", p, p2);
//	first_part(p,p2,ft_mediane(t->tab, t->size), t);
	ft_quick_sort(p,p2,ft_mediane(t->tab, t->size), t);
	/*	regle("aff", p, p2);
	regle("nb", p, p2);
	if (p2->nb_elem == 0 && (i = ft_is_sort(p)) == 1)
		printf("ok\n");
	else
		printf("ko%d\n", i);
*/	//free(str);
}
