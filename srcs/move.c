#include "lemin.h"
/*
void		display_ant_location(ENV *e, t_tab ***paths)
{
	int ant = 0;
	(void)paths;
	while (e->ants[ant])
	{
		ft_printf("ant #%d in room index = %d (comb = %d path = %d)", ant + 1, e->ants[ant][2], e->ants[ant][0], e->ants[ant][1]);
		if (e->ants[ant][0] == -2 && paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]] == e->graphe->end)
			ft_printf(" (END)");
		ft_printf("\n");
		++ant;
	}

}
*/

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
			if (curpath->tab[(int)ft_abs(e->ants[i][2])] == room)
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
	if (!e->ants)
		return ;
	while (e->ants[ant])
		++ant;
	j = -1;
	while (++j < ant)
	{
		if ((comb = e->ants[j][0]) != -2 
				&& (int)ft_abs(e->ants[j][2]) + 1 < (paths[comb][e->ants[j][1]])->length)
		{

			if (!ant_in_room(e, paths, j, paths[comb][e->ants[j][1]]->tab[(int)ft_abs(e->ants[j][2]) + 1]))
			{
				if (!e->ants[j][2] && paths[e->ants[j][0]][e->ants[j][1]]->tab[0])
					--paths[e->ants[j][0]][e->ants[j][1]]->tab[0];
				e->ants[j][2] = (int)ft_abs(e->ants[j][2]) +  1;
			}
			else
				e->ants[j][2] = -(int)ft_abs(e->ants[j][2]);

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
	int j;
	int ant;

	j = 0;
	while (j < comb && !(i = 0))
	{
		while (!(ant = 0) && paths[j][i])
		{
	//		if (!e->ants)
	//			return (ERR_ANT_NB);
			while (e->ants[ant])
				++ant;
			if (paths[j][i]->tab[0] && ant < e->ins->nb_ants)
			{
				if (!ant_in_room(e, paths, ant, paths[j][i]->tab[1]) )
				{
					if (!(e->ants[ant] = (int *)ft_memalloc(sizeof(int) * 3)))
						return (ERR_ALLOC);
					e->ants[ant][0] = j;
					e->ants[ant][1] = i;
					e->ants[ant][2] = 1;
					--paths[j][i]->tab[0];
				}
			}
			++i;
		}
		++j;
	}
	return (NO_ERR);
}


