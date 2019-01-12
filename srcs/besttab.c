
#include "lem_in.h"


t_tab	***registerPath(t_graphe *g, int nbPath, t_tab ***besttab);
t_tab	***allowBestTab(int nbPath, int sizeMax);

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


