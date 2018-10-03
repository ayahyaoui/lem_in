
#include "libft.h"

int main(int argc, const char *argv[])
{
	if (argc == 1)
		return 0;
	int *tab = malloc(argc * 4);
	for (int i = 0; i < argc - 1; i++)
		tab[i] = ft_atoi(argv[i + 1]);
	ft_tri_fusion_iterative(tab, argc-1);
	ft_affichetab(tab,argc-1,'\n');
}
