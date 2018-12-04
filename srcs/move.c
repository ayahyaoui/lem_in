#include "lemin.h"

/*
 ** Scan all ants info and check if one of them is located in room
 ** Input: full path combination, maximum ant to check, room index
 ** return 1 if room occupied, otherwise 0
 */

static int	ant_in_room(ENV *e, t_tab ***paths, int ant, int room)
{
	int 	i;
	t_tab	*curpath;

	i = -1;
	if (room == e->graphe->end)
		return (0);
	while (++i < ant)
	{
		if (e->ants[i][0] != -2 && paths[e->ants[i][0]]
				&& (curpath = paths[e->ants[i][0]][e->ants[i][1]]))
		{
			if (curpath->tab[e->ants[i][2]] == room)
				return (1);
		}
	}
	return (0);

}

/*
 ** For all ants, if ant in anthill, check if next room on path is free, and move to that room if so 
 */

void		move_next_room(ENV *e, t_tab ***paths)
{
	int j;
	int ant;
	int comb;

	ant = 0;
	while (e->ants[ant])
		++ant;
	j = -1;
	while (++j < ant)
	{
		if ((comb = e->ants[j][0]) != -2 
				&& e->ants[j][2] + 1 < (paths[comb][e->ants[j][1]])->length)
		{
			if (!ant_in_room(e, paths, j, paths[comb][e->ants[j][1]]->tab[e->ants[j][2] + 1]))
				e->ants[j][2] += 1;
		}
	}
}

/*
 ** Scan downwards through combinations, scan upwards through paths - check in index 0 of paths if ants
 ** are still outside the anthill and if room free from ants, add location info to ant tab (combination, paths,** number of room from entrance 
 */

int	ant_enter_path(ENV *e, t_tab ***paths, int comb)
{
	int i;
	int ant;

	while (comb >= 0 && !(i = 0))
	{
		while (!(ant = 0) && paths[comb][i])
		{
			while (e->ants[ant])
				++ant;
			if (paths[comb][i]->tab[0] && ant < e->ins->nb_ants
					&& !ant_in_room(e, paths, ant, paths[comb][i]->tab[1]))
			{
				if (!(e->ants[ant]= (int *)ft_memalloc(sizeof(int) * 3)))
					return (ERR_ALLOC);
				e->ants[ant][0] = comb;
				e->ants[ant][1] = i;
				e->ants[ant][2] = 1;
				--paths[comb][i]->tab[0];
			}
			++i;
		}
		--comb;
	}
	return (NO_ERR);
}


