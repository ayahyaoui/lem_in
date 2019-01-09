/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/08 23:29:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



#define PATH_SIZE 16;

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

void	printAnt(t_graphe *g, int res, int *tab);
int		ajout_chemins(t_graphe *g);
void	algoopti(t_graphe *g, t_input *infos);
void		print_lastpath(t_graphe *g, t_input *infos);
t_tab		***edmondKarp(t_graphe *g);
void	infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);




void	algoopti(t_graphe *g, t_input *infos)
{
	t_tab ***besttab = edmondKarp(g);
(void)infos;
bestsimulation(g, infos, besttab);
	free_besttab(besttab);
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
*/


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

int first = 0;
/*
void	registerPath(t_graphe *g, int newas, t_tab *** besttab)
{
	int val;
	int i;
	t_node *node;

	i = -1;
	val = -1;
	while (++i < (int)g->nb_rooms)
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0 && g->capacite[i] > val)
			val = g->capacite[i];
	if (val > 0)
	{
		while (!(val & binaire))
			binaire = binaire >> 1;
	}else
		binaire = 1;
	if (news)
		binaire = binaire << 1;
	ft_printf("binaire == %u %d", binaire, news);
	while (++i < (int)g->nb_rooms)
	{
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0)
			while ((node = g->node[i])->value != g->start)
			{
				if (!(g->capacite[i] & binaire))
					g->capacite[i] += binaire;
				node = g->node[node->parent];
			}
	}
}
*/

t_tab	***allowBestTab(int nbPath, int sizeMax)
{
	t_tab ***besttab = 0x0;
	int i;
	int a;

	ft_printf("je suis appele une seule fois !!!!!!!%llu * %d = %lld\n",
			sizeof(t_tab), sizeMax, sizeMax* sizeof(t_tab));
	if (!(besttab = (t_tab***)ft_memalloc(sizeof(t_tab**) * (nbPath + 1))))
		exit(ERRORMALLOC);
	a = -1;

	while (++a < nbPath)
	{
		if (!(besttab[a] = ft_memalloc(sizeof(t_tab *) * (nbPath  + 1))))
			exit(ERRORMALLOC);
		i = -1;
		while (++i < nbPath)
		{
			if (!(besttab[a][i] = (t_tab*)ft_memalloc(sizeof(t_tab))))
				exit(ERRORMALLOC);
			if (!(besttab[a][i]->tab = ft_memalloc(sizeof(int) * (sizeMax + 1))))
				exit(ERRORMALLOC);
		}
		besttab[a][i] = 0x0;
	}
	besttab[a] = 0x0;
	return (besttab);
}

int		addPath(t_node *node, t_graphe *g, t_tab *t)
{
	int pos;

	if (node->value == g->start)
	{
		t->tab[0] = g->start;
		return 1;
	}
	pos = addPath(g->node[node->parent], g, t);
	t->tab[pos] = node->value;
	return pos + 1;
}

t_tab	***registerPath(t_graphe *g, int nbPath, int sizeMax, t_tab ***besttab)
{
	int i;
	int j;
	(void)sizeMax;

	//besttab = allowBestTab(nbPath, g->nb_rooms, besttab);
	i = -1;
	j = 0;
	while (++i < (int)g->nb_rooms)
	{
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0)
		{
			besttab[nbPath][j]->length = addPath
				(g->node[i], g, besttab[nbPath][j]);
			j++;
		}
	}
	besttab[nbPath][j] = 0x0;
	return besttab;
}

t_tab		***edmondKarp(t_graphe *g)
{
	int i;
	t_node *node;
	t_node *next;
	int		nbmap;
	t_tab ***besttab;

	nbmap = 0;
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
		ft_printf("\n\najout_chemins%d\n", first++);
		i = g->node[g->end]->previous;
		node = g->node[i];
		
		while (node->value != g->start)
		{
			next = g->node[node->previous];
			if (g->color[node->previous] == 0)
				node->parent = node->previous;
			else
				nbmap = 1;
			node = next;
		}
		registerPath(g, first - 1, 0, besttab);
		//afficheAllParent(g);
	}
//	besttab[first] = 0x0;
	printf("finishhhh\n");
	return (besttab);
}

int		IsinIntTab(int *tab, int len, int value)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (value == tab[i])
			return (1);
	}
	return (0);
}

int		searchIntTab(int *tab, int len, int value)
{
	int i;

	i = -1;
	while (++i < len)
		if (value == tab[i])
			return (i);
	return (-1);
}

void	move(t_graphe *g, t_tab ***besttab)
{
	int i;
	int j;
	t_tab *t;
	int *tmp;

	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	//printAnt(g,0, g->capacite);
	i = -1;
	while (++i < ((int)g->nb_rooms))
		if (g->color[i] > 0)
		{
			j = -1;
			while (besttab[g->color[i] - 1][++j])
			{
				t = besttab[g->color[i] - 1][j];
				if (IsinIntTab(t->tab, t->length , i))
				{
					j = searchIntTab(t->tab, t->length, i);
				//	ft_print_inttab(t->tab, t->length, ' ');
					//ft_printf("je recherche %d dans le tab res = %d\n", i, j);
					break;
				}
			}
			j++;
			if (j == t->length)
				ft_printf("une fourmis est arrive a destination");
			else if (g->capacite[t->tab[j]] == 0)
				g->capacite[t->tab[j]] = g->color[i];
			else if (g->capacite[i] == 0)
				g->capacite[i] = g->color[i];
			else
				ft_printf("une fourmis vient de disparaitre en %d\n", i);
		}
	tmp = g->color;
	g->color = g->capacite;
	g->capacite = tmp;
	//ft_printf("move terminer\n");
	//printAnt(g, 0, g->capacite);
}

void		add(t_graphe *g, int *tab, t_tab ***besttab)
{
	int i;
	int j;
	
	i = (int)(g->nb_rooms);
	while (i > 0 && tab[i] == 0)
		i--;
	j = -1;
	ft_printf(" add est appele");
	if (i == 0 && tab[0] == 0)
		return;
	while (++j <= i)
	{
		//ft_printf("val = %d ", besttab[i][j]->tab[1]);
		if (g->color[besttab[i][j]->tab[1]] == 0)
		{
		//	ft_printf("yes");
			g->color[besttab[i][j]->tab[1]] = i + 1;
			tab[i]--;
		}
	}
}

int			isfinish(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	while (++i < (int)(g->nb_rooms))
	{
		if (tab[i] > 0 || (i != g->end && g->color[i] != 0))
			return (0);
	}
	return (1);
}

void	printAnt(t_graphe *g, int res, int *tab)
{
	ft_printf("Tour numero %d \n", res);
	ft_print_inttab(g->color, (int)g->nb_rooms, ' ');
	ft_print_inttab(tab, g->nb_rooms, ' ');

}

int			simulation(t_graphe *g, int *tab, t_tab ***besttab)
{
	int res;
	ft_bzero(g->color, sizeof(int) * g->nb_rooms);
	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	displayallpath(g, besttab);


	res = 0;
	while (1)
	{
		ft_printf("nouveau tour (%d)", res);
		//ft_print_inttab(tab, g->nb_rooms, ' ');
		move(g, besttab);
		add(g, tab, besttab);
		if (res > 10|| isfinish(g, tab))
			break;
		res++;
	}
	return res;

}


void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab)
{
	int *tab = ft_memalloc(sizeof(int) *g->nb_rooms);
	int min = 2000000000;
	tab[first - 1] = infos->nb_ants;
	
	min = simulation(g, tab, besttab);

	ft_printf("resultat == %d", min);
	free(tab);
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

