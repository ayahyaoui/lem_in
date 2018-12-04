
#include"lemin.h"

void			print_rooms(ENV *e, char **room) // only for debug, delete
{
	int i;

	i = -1;
	ft_printf("list of %d rooms", e->graphe->nb_rooms);
	while ((unsigned int)++i < e->graphe->nb_rooms)
		ft_printf("%s ", room[i]);
	ft_printf("\n");
}


void	printlist(ENV *e, t_list *l)
{	
	t_list *tmp;

	(void)e;
	tmp = l;
	ft_printf("print list of rooms\n");
	while (tmp)
	{
		ft_printf("%s\t", (char *)(tmp->content));
		tmp = tmp->next;
	}
}

void		display_adj_mtrx(ENV *e, char **tab, int size)
{
	int	i;
	int	j;	

	i = -1;
	ft_printf("display adj mtrx\n");
	ft_printf("\t | ", i);
	while (++i < size)
		ft_printf("%s\t", e->ins->room[i].name);
	ft_printf("\n");
	j = -1;
	while (++j < size)
	{
		i = -1;
		ft_printf("%s\t | ", e->ins->room[j].name);
		while (++i < size) 
			ft_printf("%d\t", tab[j][i]);
		ft_printf("\n");
	}

}


