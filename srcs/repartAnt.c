
#define ABS(X) (X > 0) ? X : -1 * X

#include "lem_in.h"


void		infos_graphes(t_graphe *g);
void		move(t_graphe *g, t_tab ***besttab);
void		add(t_graphe *g, int *tab, t_tab ***besttab);
int			isfinish(t_graphe *g, int *tab);
int			isfinishh(t_graphe *g, int *tab);
void		printAnt(t_graphe *g, int res, int *tab);
int			simulation(t_graphe *g, int *tab, t_tab ***besttab);
int			changeTab(int *tab);
void		addAnt(t_graphe *g, t_tab **besttab, int nbAnt);
void		vielleSimulation(t_graphe *g, t_tab ***besttab, int fourmis);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);

int fourmis = 0;
extern int first;

int		searchIntTab(int *tab, int len, int value)
{
	int i;

	i = -1;
	while (++i < len)
		if (value == tab[i])
			return (i);
	return (-1);
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
		ft_printf("seggggggggggg\n");
		pass = 0;
		j = -1;
		while (++j < nb_chemin)
		{
			if (i >= simulation[j])
			{
				pass++;
				besttab[first][j]->tab[0]++;
	//			ft_printf("%d",besttab[first][j]->length);
			}
		}
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



void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab)
{
	int *tab = ft_memalloc(sizeof(int) *g->nb_rooms);
//	int min = 2000000000;
	//int calcul;
//	int i;
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
	/*		i = -1;
			while (++i < (int)g->nb_rooms)
				if (t[i] > 0)
				{
					addAnt(g, besttab[i], infos->nb_ants);
*/
					//}
	//	}
	//}
	vielleSimulation(g, besttab, infos->nb_ants);
	//int test = test_simulation()
	ft_printf("resultat == rien");
	displayallpath(g, besttab);
	free(tab);
	free(t);
}

