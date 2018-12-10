
#include "lem_in.h"

/*
 * ceci n'est pas optimise l'objectif est de convertir l'ancien parsing en un
 * nouveau dans un premier temp chaque element va
 * on considere que map est ne taille nb_rooms * 2
 * chaque noeud pointe non plus sur son voisin mais son voisin + nb_rooms
 * pour regler le probleme ou plusieur arrete pointes sur le meme noeud
 * et que ce dernier pointes sur plusieur autre noeud
 * mtn toute la deuxieme ^partie du graphe n'a qu'un seule voisin
 */

void		affiche_allpaths(t_graphe *g, t_input *infos);
int		algoquidechire(t_graphe *g, t_input *infos);
int		**creategraph(int len)
{
	int **map;
	int i;

	if (!(map = (int**)malloc(sizeof(int*) * (len * 2 + 1))))
		exit(ERRORMALLOC);
	i = -1;
	while (++i < len)
	{
		if (!(map[i] = (int*)ft_memalloc(sizeof(int) * (len + 1))))
			exit(ERRORMALLOC);
	}
	/*while (i < 2 * len)
	{
		if (!(map[i] = (int*)ft_memalloc(sizeof(int) * 2)))
			exit(ERRORMALLOC);
		i++;
	}*/
	map[i] = 0x0;
	return map;
}

void		convert(t_graphe *g , t_input *infos)
{
	unsigned int i;
	int j;
	int room;

	g->graph = creategraph(g->nb_rooms);
	i = 0;
	g->previous = ft_memalloc(g->nb_rooms * sizeof(int));
	while (i < g->nb_rooms)
	{
		j = -1;
		room = -1;
		while ((unsigned int)++j < g->nb_rooms)
			if (g->map[i][j] == 1)
				g->graph[i][++room] = j;
		g->graph[i][room + 1] = -1;
		i++;
	}
	/*while (i < g->nb_rooms)
	{
		g->map[i][0] = i - g->nb_rooms;
		g->map[i][1] = -1;
		i++;
	}*/
	if (!(g->capacite = (int*)ft_memalloc(g->nb_rooms * sizeof(int))))
		exit(ERRORMALLOC);
	for (unsigned int j = 0; j < g->nb_rooms ; j++)
		g->capacite[j] = -1;
	ft_bzero(g->color, g->nb_rooms * sizeof(int));
	g->file = new_file(g);
	g->end =  1;
	ft_putstr("==========================GO==============================\n");
	algoquidechire(g, infos);
}

int		ajout_chemin(t_graphe *g)
{
	int node;
	int i;
	int tmp;

	node = g->start;
	g->color[node] = BLACK;
	addfile(g->file, node);
	while (g->file->begin < g->file->end)
	{
		node = removefile(g->file);
		//ft_printf("<%d>\n", node);
		if (node == g->end)
			return (1);
		//if (g->capacite[node] != -1)
		//	ft_printf("pb %d sur le node %d\n", g->capacite[node], node);
		if (g->capacite[node] != -1 && (g->color[g->capacite[node]]) == WHITE)
		{
			i = g->capacite[node];
			addfile(g->file, i);
			g->color[i] = BLACK;
			g->previous[i] = node + g->nb_rooms;
		}
		else
		{
			i = 0;
			while (g->graph[node][i] != -1)
			{
				tmp = g->graph[node][i];
				//printf("link %d->%d\n", node, tmp);
				if (g->color[tmp] == WHITE && (g->capacite[tmp] == -1 ||
				(g->capacite[tmp] != -1 && g->map[node][tmp] == 1)))
				{
				//	printf("add %d\n", tmp);
					g->color[tmp] = BLACK;
					addfile(g->file, tmp);
					g->previous[tmp] = node;
				}
				i++;
				//if ()
			}
			//ft_printf("loop finish\n");
		}
	}
	return (-1);
}

int		algoquidechire(t_graphe *g, t_input *infos)
{
	//ft_printf("reussi %d\n",ajout_chemin(g));
	int i;
	int exept;
	while (1)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		ft_bzero(g->color, g->nb_rooms * sizeof(int));
		ft_mem_set_int(g->previous, -1, g->nb_rooms);
		if (ajout_chemin(g) == -1)
			break;
		i = g->end;
			exept = 0;
		while (i != g->start)
		{
			//ft_printf("%d <-", i);
			if (g->previous[i] > 0 && 
			(unsigned int)g->previous[g->previous[i]] >= g->nb_rooms)
			{
				g->previous[g->previous[i]] -= g->nb_rooms;
				exept = 1;
			}
			g->capacite[i] = g->previous[i];
			if (exept == 2)
				exept = 0;
			else
				g->map[g->previous[i]][i] = 2;
			g->map[i][g->previous[i]] = 1;
			i = g->previous[i];
			if (exept == 1)
			{
				exept++;
				g->map[g->previous[i]][i] = 1;
			}
			//ft_putstr("- ");
		}
			//ft_printf("%d\n", g->start);
	}
			//	g->map[2][1] = 1;
	affiche_allpaths(g, infos);
	free_file(&g->file);
/*	i = g->end;
	while (i != g->start)
	{
		ft_printf("%d <-- ", i);
		i = g->previous[i];
	}
	ft_printf("%d\n", g->start);
*/	return 1;
}

void		affiche_allpaths(t_graphe *g, t_input *infos)
{
	int i;
	int j;
	int k;
	int	nb_chemin = -1;
	int longeurmax = 0;
	int longueur = 0;
	int *simulation = malloc(4 * g->nb_rooms);


	i = -1;
	while ((unsigned int)++i < g->nb_rooms)
		if (g->map[g->start][i] == 2)
		{
			ft_printf("%d -->", g->start);
			j = i;
			longueur = 1;
			while (j != g->end)
			{
				longueur++;
				if (longueur > longeurmax)
					longeurmax = longueur;
				k = -1;
				while ((unsigned int)++k < g->nb_rooms)
					if (g->map[j][k] == 2)
					{
						ft_printf("%d -->", j);
						j = k;
						break;
					}
				if ((unsigned int)k == g->nb_rooms)
					exit(1);
			}
			ft_printf("%d\n", g->end);
			simulation[++nb_chemin] = longueur;
			ft_printf("chemin numero %d = %d\n", nb_chemin ,simulation[nb_chemin]);
			ft_putstr("\n\n");
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
		ft_printf("tour (%d,%d)", i,pass);
		fourmis-=pass;
		i++;
	}
	printf("\npire des cas via simulation = %d\n", i - 1);
}

