#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "lem-in.h"

void	getleaks(char *str)
{

	ft_printf("%s %s %s\n", COLB_MAGENTA, str, COLB_OFF);
	system("leaks lem-in");
	getchar();
}
