/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/11 14:14:16 by anyahyao         ###   ########.fr       */
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

void		printAnt(t_graphe *g, int res, int *tab);
int			ajout_chemins(t_graphe *g);
t_tab		***algoopti(t_graphe *g, t_input *infos);
void		print_lastpath(t_graphe *g, t_input *infos);
t_tab		***edmondKarp(t_graphe *g);
void		infos_graphes(t_graphe *g);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);




t_tab	***algoopti(t_graphe *g, t_input *infos)
{
	t_tab ***besttab = edmondKarp(g);
(void)infos;
bestsimulation(g, infos, besttab);
	ft_printf("============================================================");
	ft_printf(" PREMIERE PARTIE FINIS ");
	ft_printf("============================================================\n");
	ft_printf("il y'a %d fourmis\n", infos->nb_ants);
	displayallpath(g, besttab);
	return (besttab);
//	free_besttab(besttab);
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

	ft_printf("je suis appele une seule fois !!!!!!!%llu * %d = %lld\n",
			sizeof(t_tab), sizeMax, sizeMax* sizeof(t_tab));
	if (!(besttab = (t_tab***)ft_memalloc(sizeof(t_tab**) * (nbPath + 1))))
		exit(ERRORMALLOC);
/*
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
	*/
	return (besttab);
}

int		addPath(t_node *node, t_graphe *g, t_tab *t)
{
	int pos;

//	ft_printf("add path | node value = %d start = %d\n", node->value, g->start);
	if (node->value == g->start)
	{
		t->tab[0] = g->start;
		return 1;
	}
	pos = addPath(g->node[node->parent], g, t);
	t->tab[pos] = node->value;
	return pos + 1;
}
t_tab	**allowTab(t_graphe *g, t_tab **besttab)
{
	int i;
	int j;
//	int a;
	int sizeMax;
	t_node *node;

	ft_putstr("allowBestTab\n");
	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	i = -1;
	j = 0;
	sizeMax = -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0)
		{
			node = g->node[i];
			g->capacite[i]+=1;
			while (node->value != g->start)
			{
				node = g->node[node->parent];
				g->capacite[i]+=1;
			}
			if (g->capacite[i] > sizeMax)
				sizeMax = g->capacite[i];
			j++;
		}
	}
	ft_printf("la plus grade fairet %d et %d\n", sizeMax, j);
//	a = 0;
	if (!(besttab = ft_memalloc(sizeof(t_tab *) * (j  + 1))))
		exit(ERRORMALLOC);
	i = -1;
	while (++i < j)
	{
		if (!(besttab[i] = (t_tab*)ft_memalloc(sizeof(t_tab))))
			exit(ERRORMALLOC);
		if (!(besttab[i]->tab = ft_memalloc(sizeof(int) * (sizeMax + 2))))
			exit(ERRORMALLOC);
	}
	besttab[j] = 0x0;
	return (besttab);
}

void	placeValueInTab(int *tab, int value, int pos)
{
	int tmp;

	while (tab[pos] >=  0)
	{
		tmp = tab[pos];
		tab[pos] = value;
		value = tmp;
		pos++;
	}
	tab[pos] = value;
}


int		SortPath(t_graphe *g)
{
	int i;
	int j;

	ft_memset(g->previous, -1,sizeof(int) * g->nb_rooms);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->capacite[i] > 0)
		{
			j = 0;
			while (g->previous[j] >= 0 && g->capacite[i] > g->capacite[g->previous[j]])
				j++;
			ft_printf("val = %d pos = %d et j = %d", g->capacite[i], i, j);
			placeValueInTab(g->previous, i, j);
		}
	}
	return (1);
}

t_tab	***registerPath(t_graphe *g, int nbPath, t_tab ***besttab)
{
	int i;
//	int j;

	//besttab = allowBestTab(nbPath, g->nb_rooms, besttab);
	i = -1;
//	j = 0;
	if (nbPath >= 50)
		exit(1);
	besttab[nbPath] = allowTab(g, besttab[nbPath]);
	i = 0;
	SortPath(g);
	ft_print_inttab(g->previous, g->nb_rooms, ' ');
//	ft_printf("allocation nb path = %d\n", nbPath);
	while (g->previous[i] >= 0)
	{
//		ft_printf("previous = %d\n", g->previous[i]);
		besttab[nbPath][i]->length = addPath(g->node[g->previous[i]], g, besttab[nbPath][i]) + 1;
		besttab[nbPath][i]->tab[besttab[nbPath][i]->length - 1] = g->end;
		ft_printf("i = %db = %d", i,besttab[nbPath][i]->tab[1]);
//		ft_printf("display path: \n");
//		for (int j = 0; j < besttab[nbPath][i]->length; j++)
//			ft_printf("%d ", besttab[nbPath][i]->tab[j]);
//		ft_printf("\n");
//		besttab[nbPath][i]->tab[0] = 
//		ft_printf("length = %d\n", besttab[nbPath][i]->length);
//		--g->previous[i];
		++i;
//		ft_printf("next previous = %d\n", g->previous[i]);
	}
//	besttab[0][0]->tab[0] = 1;
//	besttab[0][1]->tab[0] = 2;
	
//	ft_printf("nb path = %d i = %d length = %d\n", nbPath, i, besttab[nbPath][i - 1]->length - 1);
//	ft_printf("il y'a %d chemin en %d", i, nbPath);
	//besttab[nbPath][i + 1] = 0x0;
	return besttab;
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

t_tab		***edmondKarp(t_graphe *g)
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
int fourmis = 0;

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
			if (j == t->length - 1)
				fourmis ++;//ft_printf("une fourmis est arrive a destination");
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

void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis)
{
	int i;
	int j;
	int	nb_chemin = -1;
	int longeurmax = 0;
	int *simulation = malloc(4 * g->nb_rooms);
	int pass;

	for (i = 0; besttab[first][i] ; i++) {
		simulation[i] = besttab[first][i]->length;
		if (simulation[i] > longeurmax)
			longeurmax = simulation[i];
	}
	nb_chemin = i;

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





void		add(t_graphe *g, int *tab, t_tab ***besttab)
{
	int i;
	int j;

	i = (int)(g->nb_rooms);
	while (i > 0 && tab[i] <= 0)
		i--;
	j = -1;
//	ft_printf(" add est appele, i = %d\n", i);
	if (i == 0 && tab[0] == 0)
		return;
	while (besttab[i][++j])
	{
		//ft_printf("val = %d ", besttab[i][j]->tab[1]);
		if (tab[i] > 0 && g->color[besttab[i][j]->tab[1]] == 0)
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
	ft_printf("nb rooms = %d\n", g->nb_rooms);
	while (++i < (int)(g->nb_rooms))
	{
		ft_printf("i = %d nb rooms = %d\n", i, g->nb_rooms);
		if (tab[i] > 0 || (i != g->end && g->color[i] != 0))
			return (0);
	}
	return (1);
}
int			isfinishh(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	while (++i < (int)(g->nb_rooms))
	{
		if (tab[i] > 0 || (i != g->end && g->color[i] != 0))
		{
			ft_printf("probleme en %d",i);
			return (0);
		}
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
	//displayallpath(g, besttab);


	res = 0;
	//printAnt(g, res, tab);
	while (1)
	{
		//ft_printf("nouveau tour (%d)", res);
		move(g, besttab);
		add(g, tab, besttab);
		if (isfinish(g, tab))
			break;
		res++;
	}
	//ft_print_inttab(tab, g->nb_rooms, ' ');
	//printAnt(g, res, tab);
	//isfinishh(g, tab);
	infos_graphes(g);
	return res;

}
/*
 *	a faire
 */
int changeTab(int *tab)
{
	(void)tab;
	return (1);
}

#define ABS(X) (X > 0) ? X : -1 * X

/*
 *	par du principe que besttab est triee
 */

void		addAnt(t_graphe *g, t_tab **besttab, int nbAnt)
{
	int i;
	int j;
	int k;
	(void)g;
	i = -1;

	//displayallpath(besttab);
	ft_printf("il y'a %d foumis a placer\n", nbAnt);
	while (besttab[++i + 1] && nbAnt > 0)
	{
		//ft_printf("debut : %d %d\n", nbAnt/(i+1), besttab[i + 1]->length);
		if ((nbAnt / (i + 1)) > (besttab[i + 1]->length - besttab[i]->length))
		{
			k = besttab[i + 1]->length - besttab[i]->length;
			//	ft_printf("%d] k = %d \n", i, k);
			j = i + 1;
			while (--j >= 0)
			{
				nbAnt -= k;
				besttab[j]->tab[0] += k;
			}
		}
		else
		{
			//	ft_printf("%d} ", i);
			j = -1;
			while (++j <= i && nbAnt > 0)
			{
				nbAnt--;
				//		ft_printf("%d)\n", j);
				besttab[j]->tab[0] = besttab[j]->tab[0] + 1;
			}
		}
	}
	i++;
	j = -1;
	ft_printf("il reste %d fourmis a placer\n", nbAnt);
	k = nbAnt / i;
	while (++ j < i)
	{
		besttab[j]->tab[0] += k;
		if (j < nbAnt % i)
			besttab[j]->tab[0]++;
	}
}

void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab)
{
	int *tab = ft_memalloc(sizeof(int) *g->nb_rooms);
	int min = 2000000000;
	//int calcul;
	int i;
	tab[first] = infos->nb_ants;
	int *t = ft_memalloc(sizeof(int) *g->nb_rooms);
	t[first] = infos->nb_ants;
	displayallpath(g, besttab);
	ft_printf("on verifie %d\n", first - 1);
	//while (changeTab(tab) && min == 2000000000)
	//{
		//calcul = simulation(g, tab, besttab);
	//	if (calcul < min)
	//	{
	//		min = 18;
			i = -1;
			while (++i < (int)g->nb_rooms)
				if (t[i] > 0)
				{
					addAnt(g, besttab[i], infos->nb_ants);

					}
	//	}
	//}
	vielleSimulation(g, besttab, infos->nb_ants);
	//int test = test_simulation()
	ft_printf("resultat == %d", min);
	displayallpath(g, besttab);
	free(tab);
	free(t);
}






void	infos_graphes(t_graphe *g)
{
	ft_printf("nb_rooms = %d, nb_tubes = %d\n", g->nb_rooms, g->nb_tubes);
	ft_printf("start = %d, end = %d\n", g->start, g->end);

	/*ft_putstr("best paths:\n");
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
	  }*/
}

