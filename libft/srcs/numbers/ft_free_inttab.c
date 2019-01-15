#include "libft.h"

void		ft_free_inttab(int ***tab, int size)
{
	int	i;
	
	i = -1;
	if (tab && !*tab)
		return ;
	while (++i < size && (*tab)[i])
	{
		ft_memdel((void **)&(*tab)[i]);
	}
	ft_memdel((void **)tab);

}
