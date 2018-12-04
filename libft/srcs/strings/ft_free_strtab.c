
#include "libft.h"

void		ft_free_strtab(char ***tab)
{
	char	**tmp;

	if (!*tab)
		return ;
	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_strdel(tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}
