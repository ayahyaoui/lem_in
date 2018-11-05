#include "libft.h"

int		ft_isintab(int *tab, int len, int val)
{
	int i;

	i = -1;
	while (++i < len)
		if (tab[i] == val)
			return (1);
	return (0);
}
