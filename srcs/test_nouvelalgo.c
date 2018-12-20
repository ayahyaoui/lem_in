#include "lem_in.h"

void		nouvelletent(t_graphe *g, int **map)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < g->nb_rooms)
	{
		map[i][0] = i + g->nb_rooms;
		map[i][1] = -1;
	}
	i = -1;
	while (++i < g->nb_rooms)
	{
		j = -1;
		k = 0;
		while (++j < g->nb_rooms)
			if (g->map[i][j] == 1)
				map[i + g->nb_rooms][k++] = j;
	}
}
































int main(int argc, const char *argv[])
{
	
	return 0;
}
