/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/07 16:40:09 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"





/*
typedef struct		s_graphe
{
	unsigned int			nb_rooms; // anciennement taille
	unsigned int			nb_tubes;// inutile
	int						*color;// char *
	t_file					*file;
	int						*previous;// permet de trouver un chemin rapidement
	int						*capacite;// transorme en parent valide au tour precedent

	char					**map; // bientot capacite
	int						**graph;//prend  pas mal de place mais permet opti 

	int						*besttab;
	int						start;
	int						end;
}						t_graphe;
*/

int		ajout_chemins(t_graphe *g);
void	algoopti(t_graphe *g, t_input *infos);
void		print_lastpath(t_graphe *g, t_input *infos);
int		edmondKarp(t_graphe *g);
void	infos_graphes(t_graphe *g);




void	algoopti(t_graphe *g, t_input *infos)
{
	edmondKarp(g);
	print_lastpath(g, infos);

}



int		add_chemin(t_graphe *g)
{
	int node;
	int i;
	int tmp;

	node = g->start;
	g->color[node] = BLACK;
	addfile(g->file, node);
	while (g->file->begin < g->file->end)
	{
		if ((node = removefile(g->file)) == g->end)
			return (1);
		i = g->capacite[node];
		if (i != -1 && g->color[i] == WHITE)
		{
			addfile(g->file, i);
			g->color[i] = BLACK;
			g->previous[i] = -1;
		}
		//else
		//{
			i = 0;
			while (g->graph[node][i] != -1)
			{
				tmp = g->graph[node][i];
				if (g->color[tmp] == WHITE && (g->capacite[tmp] != node))
				{
					g->color[tmp] = BLACK;
					addfile(g->file, tmp);
					g->previous[tmp] = node;
				}
				i++;
			}
		//}
	}
	return (-1);
}


void		troisieme_tentative(t_graphe *g, t_input *infos)
{
	int i;
	int j;
	int	nb_chemin = -1;
	int longeurmax = 0;
	int longueur = 0;
	int *simulation = malloc(4 * g->nb_rooms);


	
	i = -1;
	ft_print_inttab(g->capacite, g->nb_rooms, ' ');
	while ((unsigned int)++i < g->nb_rooms)
		if (g->map[i][g->end] == 1 && g->capacite[i] != -1)
		{
			//ft_printf("%d <--", g->end);
			j = i;
			longueur = 1;
			ft_printf("loop %d=>\n", i);
			while (j != g->start)
			{
				longueur++;
				if (longueur > longeurmax)
					longeurmax = longueur;
				ft_printf("%d <-- ",j);
				j = g->capacite[j];
				if ((unsigned int)j == g->nb_rooms || j == -1)
				{ ft_printf("%d je quitte", j);exit(1);}
				//sleep(1);
			}
			//ft_printf("%d\n", g->start);
			simulation[++nb_chemin] = longueur;
			ft_printf("chemin numero %d = %d\n", nb_chemin ,simulation[nb_chemin]);
			//ft_putstr("\n\n");
		}
	ft_printf("-------------calcul du pire des cas:-----------------\n");
	ft_printf("nombre de chemin = %d\n",nb_chemin + 1);
	ft_printf("longeurmax = %d\n",longeurmax);
	ft_printf("fourmis = %d\n",infos->nb_ants);
	//ft_printf("pire des cas theorique = %d", (infos->nb_ants / nb_chemin) +longeurmax);
	int fourmis = infos->nb_ants;
	int pass;
	i = 1;

	while (fourmis > 0)
	{
		pass = 0;
		j = -1;
		while (++j <= nb_chemin)
			if (i >= simulation[j])
				pass++;
		fourmis-=pass;
		ft_printf("tour (%d,%d reste %d) ", i,pass, fourmis);
		if ((i % 5) == 4)
			ft_putstr("\n");
		i++;
	}
	free(simulation);
	simulation = 0x0;
	printf("\npire des cas via simulation = %d\n", i - 1);
}



/*
 * tout le resultat devra se trouver dans un tableau a une dimension 
 * parent a le meme role que previous mais est global
 * previous est local et represente pour chaque node ou est son precedent
 *
 */




int		edmondKarp(t_graphe *g)
{
	int i;
	int next;
	//int tmp

	while (1)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		ft_bzero(g->color, g->nb_rooms * sizeof(int));
		ft_mem_set_int(g->previous, -1, g->nb_rooms);
		ft_putstr("ajout_chemins");
		if (ajout_chemins(g) == -1)
			break;
		next = 0;
		i = g->previous[g->end];
		while (i != g->start)
		{
			//if (g->capacite[i] != -1 && g->previous[i] != g->capacite[i])
			//	next = 1;
//if (g->previous[i] == 1 || i == 1)
//	ft_printf("(%d)%d = %d\n\n\n\n\n", i, g->capacite[i], g->previous[i]);
			if (g->previous[i] > -1)
			{
				//ft_printf("{%d}", i);
				g->capacite[i] = g->previous[i];
				i = g->previous[i];
			}/*else
			{
				tmp = -1;
				while (g->capacite[++tmp] != i && (unsigned int)tmp < g->nb_rooms);
				if (g->capacite[tmp] == )
					i = tmp;
				ft_printf("[%d]", i);
			}*/
		}
		if (next == 1)
			ft_putstr("nouveau chemin trouver !!!!!!!!!!\n");
		else

		ft_printf("\n\n=>");
	//	infos_graphes(g);
	}
	return (1);
}


void	infos_graphes(t_graphe *g)
{
	ft_printf("nb_rooms = %d, nb_tubes = %d\n", g->nb_rooms, g->nb_tubes);
	ft_printf("start = %d, end = %d\n", g->start, g->end);
	
	ft_putstr("best paths:\n");
	ft_print_inttab(g->capacite, g->nb_rooms, ' ');
	
	ft_printf("map\n");
	unsigned int i,j;
	for (j = 0; j < g->nb_rooms; j++)
		ft_printf("%2u ",j);
		ft_putstr("\n");

	for (i = 0; i < g->nb_rooms; i++) {
		for (j = 0; j < g->nb_rooms; j++) {
			ft_printf("%2d ",g->graph[j][i]);
		}
		ft_putstr("\n");
		
	}

}
