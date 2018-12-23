#include "libft.h"

void		ft_print_inttab(int *tab, int len, char c)
{
	int i;

	i = -1;
	if (!tab || len < 0)
		return ;
	while (++i < len/* && tab[i]*/)
		ft_printf("%d%c", tab[i], i == len - 1 ? '\n': c);
}
