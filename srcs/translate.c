
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
	while (i < 2 * len)
	{
		if (!(map[i] = (int*)ft_memalloc(sizeof(int) * 2)))
			exit(ERRORMALLOC);
		i++;
	}
	map[i] = 0x0;
	return map;
}

void		convert(t_graphe *g)
{
	unsigned int i;
	int j;
	int room;

	g->graph = creategraph(g->nb_rooms);
	i = 0;
	g->previous = ft_memalloc(g->nb_rooms);
	while (i < g->nb_rooms)
	{
		j = -1;
		room = -1;
		while ((unsigned int)++j < g->nb_rooms)
			if (g->map[i][j] == 1)
				g->map[i][++room] = j + g->nb_rooms;
		g->map[i][room + 1] = -1;
		i++;
	}
	while (i < g->nb_rooms)
	{
		g->map[i][0] = i - g->nb_rooms;
		g->map[i][1] = -1;
		i++;
	}
}

/*
int		ajout_chemin(t_graphe *g, t_file *file)
{
	int node;
	int i;

	node = g->start;
	g->color = GREY;
	addfile(file, node);
	while (file->begin != file->end)
	{
		node = removefile(file);
		if (node == g->end)
			return (1);
		i = 0;
		while (g->graph[i] != -1)
		{
			
		}
	}
	return (-1);
}

*/

