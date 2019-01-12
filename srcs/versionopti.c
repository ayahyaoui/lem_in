/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/12 18:15:51 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//

#define PATH_SIZE 16;

int first = 0;
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

void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
t_tab	***registerPath(t_graphe *g, int nbPath, t_tab ***besttab);
t_tab	***allowBestTab(int nbPath, int sizeMax);
void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
int			algoopti(t_graphe *g, ENV e);
void		print_lastpath(t_graphe *g, t_input *infos);
int			edmondKarp(t_graphe *g, ENV e);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);




int			algoopti(t_graphe *g, ENV e)
{
	ft_printf("============================================================");
	ft_printf(" PREMIERE PARTIE FINIS ");
	ft_printf("============================================================\n");
	return (edmondKarp(g, e));
/*bestsimulation(g, infos, besttab);
	ft_printf("il y'a %d fourmis\n", infos->nb_ants);
	displayallpath(g, besttab);
	return (besttab);
*///	free_besttab(besttab);
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
	t_node *suiv;

	node = g->node[g->start];
	node->color = BLACK;
	addfile(g->file, node->value);
	while (g->file->begin < g->file->end)
	{
		if ((node = g->node[removefile(g->file)])->value == g->end)
			return (1);
		if (node->parent != -1 && g->color[node->previous] == 0)
		{
			if (getColor(g, node->parent) == WHITE)
			{
			addfile(g->file, node->parent);
			g->node[node->parent]->color = BLACK;
			g->node[node->parent]->previous = node->value;
			g->color[node->value] = 1;
			}
		}
		else
		{
			i = 0;
			while (g->graph[node->value][i] != -1)
			{
				suiv = g->node[g->graph[node->value][i]];
				if (suiv->color == WHITE && (suiv->parent == -1 ||(suiv->parent >= 0 
				 && suiv->parent != node->value))) //node->value)
				{
					suiv->color = BLACK;
					suiv->previous = node->value;
					addfile(g->file, suiv->value);
				}
				i++;
			}
		}
	}
	return (-1);
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
		if (g->node[i]->parent == 398)
			printf("398---->%d\n", i);
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


int		breakPath(t_graphe *g, int start)
{
	t_node *node;

	node = g->node[start];
	while (node->value != g->start)
	{
		if (g->color[node->previous] != 0)
			return (1);
		node = g->node[node->previous];
	}
	return (0);
}

int			edmondKarp(t_graphe *g, ENV e)
{
	int i;
	t_node *node;
	t_node *next;
//	int		nbmap;
	t_tab ***besttab;

//	nbmap = 0;
	convertGraphe(g);
	besttab = allowBestTab(50 , 200);//(t_tab***)malloc(sizeof(t_tab**));
	ft_printf("je vais commence!!");
	while (1)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		cleanNodee(g);
		ft_bzero(g->color, g->nb_rooms * 4);
		if (ajout_chemins(g) == -1)
			break;
		ft_printf("\n\najout_chemins%d\n", first);
		i = g->node[g->end]->previous;
		node = g->node[i];
		if (breakPath(g, i)){
			registerPath(g,first, besttab);
			first++;
		}
		while (node->value != g->start)
		{
			next = g->node[node->previous];
			if (g->color[node->previous] == 0)
				node->parent = node->previous;
			else
			{
//				nbmap = 1;
				ft_printf("nouveau chemin\n");
			}
			node = next;
		}
		//afficheAllParent(g);
	}
	registerPath(g, first, besttab);
	//	besttab[first] = 0x0;
	vielleSimulation(g, besttab, e.ins->nb_ants);
	printf("finishhhh\n");
	e.all_paths = besttab;
	//displayallpath(g, e.all_paths);
	return (0);
}
