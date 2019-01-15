#include "libft.h"

void		ft_free_inttab(int ***tab, int size)
{
	int	**tmp;
	int	i;
	
	i = -1;
	if (!*tab)
		return ;
	tmp = *tab;
	while (++i < size)
	{		
//		if (tmp)
//			ft_memdel((void **)tmp);
		++tmp;
	}
	ft_memdel((void **)tab);

}
