/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:34 by anyahyao          #+#    #+#             */
/*   Updated: 2018/09/30 21:04:03 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"




void		parcours_recursif();
int			degre_graphe(t_graphe *g)
{
	int i;
	int res;
	int j;

	if (g == 0X0)
		return (-1);
	i = -1;
	res = 0;
	while (++i < g->taille)
	{
		j = -1;
		while (++j < g->taille)
			if(g->map[i][j])
				res++;
	}
	return (res / 2);
}

void		init_all_path(t_graphe *g)
{
	t_chemins	*chemins;
	int			degre;
	int			len;

	chemins = (t_chemins*)malloc(sizeof(chemins));
	degre = degre_graphe(g);
	len = (degre * g->taille / 8) + 1;

}

int main(int argc, const char *argv[])
{
	char *test = malloc(5);
	test[0] = 'b';
	test[1] = 'c';
	test[2] = 'd';
	test[3] = '\0';
	test[4] = '\0';
	printf("%d, %d et %s\n",*test, test[1], test);
	*test = *test >> 8;
	printf("%d, %det %s\n",*test, test[1], test);
	free(test);
	return 0;
}
