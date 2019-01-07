/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/07 23:11:00 by anyahyao         ###   ########.fr       */
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
	(void)infos;
	//print_lastpath(g, infos);

}

int		getColor(t_graphe *g, int pos)
{
	return g->node[pos]->color;
}



int		ajout_chemins(t_graphe *g)
{
	t_node *node;
	int i;
//	int tmp;
	t_node *suiv;
//	int parent;

	node = g->node[g->start];
	node->color = BLACK;
	addfile(g->file, node->value);
	while (g->file->begin < g->file->end)
	{
		if ((node = g->node[removefile(g->file)])->value == g->end)
			return (1);
		if (node->parent != -1 && node->previous != -1 && getColor(g, node->parent) == WHITE)
		{
			ft_printf("======%d\n", node->previous);
			addfile(g->file, node->parent);
			g->node[node->parent]->color = BLACK;
			g->node[node->parent]->previous = -1;
		}
		else
		{
			i = 0;
			while (g->graph[node->value][i] != -1)
			{
				suiv = g->node[g->graph[node->value][i]];
				//tmp = g->graph[node][i];
				if (suiv->color == WHITE && suiv->parent != node->value)
				{
					suiv->color = BLACK;
					suiv->previous = node->value;
					addfile(g->file, suiv->value);
//					g->previous[suiv->value] = node;
				}
				i++;
			}
		}
	}
	return (-1);
}


void		print_lastpath(t_graphe *g, t_input *infos)
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
void	convertGraphe(t_graphe *g)
{
	unsigned int i;

	i = 0;
	g->node = malloc(sizeof(t_node*) * g->nb_rooms);
	while (i < g->nb_rooms)
	{
		g->node[i] = malloc(sizeof(t_node));
		g->node[i]->parent = -1;
		g->node[i]->value = (int)i;
		i++;
	}
}

void	cleanNodee(t_graphe *g)
{
	unsigned int i;

	i = 0;
	while (i < g->nb_rooms)
	{
		g->node[i]->previous = -1;
		g->node[i]->color = WHITE;
		i++;
	}
}

void	afficheAllParent(t_graphe *g)
{
	unsigned int i = 0;
	t_node *node;
	printf("============\n");
	while (i < g->nb_rooms)
	{
		if (g->map[i][g->end] == 1 && g->node[i]->parent >= 0)
		{
			node = g->node[i];
			int j = -1;
			while (node->value != g->start)
			{ ++j;
				printf("(%d)<-",node->value);
				node = g->node[node->parent];
				if (node->value == 1333 && j > 15)
					exit(1);
			}
			printf("(%d)\n", g->start);
		}
		i++;
	}
	ft_bzero(g->color, g->nb_rooms * 4);
	for (i = 0; i < g->nb_rooms; i++) {
		if (g->node[i]->parent > 0)
			g->color[g->node[i]->parent]++;
	}
	for (i = 0; i < g->nb_rooms; i++) 
		if (g->color[i] > 1){
			ft_printf("probleme en %d<-%d", i, g->node[i]->parent);
			exit(1);
		}
	/*for (i = 0; i < g->nb_rooms; i++) {
		if (g->color[i] > 1)
			ft_printf("probleme en %d<-%d", i, g->node[i]->parent);
	}*/
	ft_bzero(g->color, g->nb_rooms);
			//printf("%d(%d) //// ", g->node[i]->parent, i);
}

int		edmondKarp(t_graphe *g)
{
	int i;
	int tmperror;
	t_node *node;
	t_node *tmp;
	t_node *p;
	int first = 0;

	convertGraphe(g);
	while (1)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		cleanNodee(g);
		if (ajout_chemins(g) == -1)
			break;
		ft_putstr("\n\najout_chemins\n");
		i = g->node[g->end]->previous;
		node = g->node[i];
		p = node;
		ft_printf("= = %d\n",++first);
	//	ft_printf("parent de 1333 %d et parent de 1014 %d\n", g->node[1333]->parent, g->node[1014]->parent);
		while (node->value != g->start)
		{
			//if (first == 12)
			ft_printf("<%d>\n", node->value);
			if (node->previous != -1)
			{
			p = node;
				if (node->parent == node->previous)
					ft_printf("bizare\n");
				node->parent = node->previous;
				node = g->node[node->parent];
			}
			else
			{
			//	ft_printf("<<<%d\n", first);
				i = -1;
				tmperror = 0;
				while (++i < (int)g->nb_rooms)
				{
					if (g->node[i]->parent == node->value && i != p->value )
					{
			//			sleep(1);
						ft_printf("value %d vers %d\n", node->value, i);
						tmperror++;
						if (tmperror == 1)
						{
								
							ft_printf("%d>>>%d\n", node->value,node->parent);
							g->node[i]->parent = -1;
							tmp = g->node[i];
							//ode->parent = i;;
						}
					}
				}
			p = node;
				/*if (g->node[node->parent]->parent == node->value)
				{
					printf("%d ppppppppp %d ", node->value, node->parent);
					exit(1);//printf("Error :%d\n", tmperror);
				}*/
				if (tmperror != 1)
				{
					printf("%d et %d ", tmperror, g->end);
					exit(1);//printf("Error :%d\n", tmperror);
				
				}
				if (tmperror == 0)
					return (0);
				node = tmp;
			}
			
		}
	//	if (first == 12)
		afficheAllParent(g);
	}
	return (1);
}
// 1333 1014
// 973 > 473
// 973 > 1136

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
