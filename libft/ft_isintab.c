


#include "libft.h"


int		ft_isintab(int *tab, int len, int value)
{
	int i;

	if (!tab)
		return (-1);
	i = -1;
	while (++i < len)
		if (tab[i] == value)
			return (1);
	return (0);
}
