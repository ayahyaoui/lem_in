
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
	map[i] = 0x0;
	return map;
}

int			convert_map_to_graph(t_graphe *g)
{
	int room;
	int i;

	if (!(g->graph = creategraph(g->nb_rooms)))
			return (ERR_ALLOC);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		j = -1;
		room = -1;
		while (++j < (int)g->nb_rooms)
			if (g->map[i][j] == 1)
				g->graph[i][++room] = j;
		g->graph[i][room + 1] = -1;
	}
}


// retourner int ERR_MALLOC ou ERR_SOLUTION, NO_ERR si solution valide trouvee
int			convert_graphe(t_graphe *g)
{
	int i;
	int j;
	int room;

	g->graph = creategraph(g->nb_rooms);
	g->previous = ft_memalloc(g->nb_rooms * sizeof(int));
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		j = -1;
		room = -1;
		while (++j < (int)g->nb_rooms)
			if (g->map[i][j] == 1)
				g->graph[i][++room] = j;
		g->graph[i][room + 1] = -1;
	}
	g->node = malloc(sizeof(t_node*) * g->nb_rooms);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		g->node[i] = ft_memalloc(sizeof(t_node));
		g->node[i]->parent = -1;
		g->node[i]->value = (int)i;
	}
	if (!(g->capacite = (int*)ft_memalloc(g->nb_rooms * sizeof(int))))
		exit(ERRORMALLOC);
	for (unsigned int j = 0; j < g->nb_rooms ; j++)
		g->capacite[j] = -1;
	ft_bzero(g->color, g->nb_rooms * sizeof(int));
	g->file = new_file(g);
	ft_putstr("==========================GO==============================\n");
	return (NO_ERR);
}
